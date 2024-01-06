/**
 * @file BMP.cpp
 * @author Yusuke Ota
 * @brief BMPクラスの実装部
 * @version 0.1
 * @date 2024-01-02
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Image.h"

#define WINDOWS_PALETTE_SIZE 4

BMP::BMP(const char filePath[]){
    this->filePath = filePath;
    printf("bmp instance\n");
}

const unsigned char BMP::fileSignature[2] = {0x42, 0x4d};

const char BMP::extension[4] = "bmp";

void printChars(int charLength, char* chars){
    for(int i = 0; i < charLength; i++){
        printf("%02x ", chars[i]);
    }
    printf("\n");
}

/**
 * @brief char配列をリトルエンディアンの16進数としてintに変換
 * 
 * @param charLength 一括りにしたいcharの長さ
 * @param chars 
 * @return int 
 */
int charsToInt(int charLength, unsigned char* chars){
    int result = 0;
    for(int i = charLength - 1; i >= 0; i--){
        result = result + chars[i] * pow(16, i * 2);
    }
    return result;
}

/**
 * @brief intをリトルエンディアンの16進数としてchar配列に変換
 * 
 * @param charLength 
 * @param num 
 * @return char* 
 */
unsigned char* intToChars(int charLength, unsigned int num){
    unsigned char* result = new unsigned char[charLength];
    unsigned int twoByteF = 255;

    for(int i = 0; i < charLength; i++){
        result[i] = (int)((num & (twoByteF << (8 * i))) >> (8 * i));
    }

    return result;
}


ImageData* BMP::getImageData(){
    this->filePathNullCheck();

    // ファイルデータ
    unsigned char* fileData;

    // ファイルサイズ
    int fileSize = 0;

    // ファイル解析
    FILE* file;
    if((file = fopen(filePath, "rb")) == NULL){
        printf("file open error\n");
        exit(EXIT_FAILURE);
    }
    // ファイルサイズ
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    if(fileSize < 14){
        printf("file size error\n");
        exit(EXIT_FAILURE);
    }

    // ファイル読み込み
    fileData = (unsigned char*)malloc(fileSize);
    fread(fileData, 1, fileSize, file);
    fclose(file);

    // ImageDataに格納
    ImageData* imageData = new ImageData();
    int bfOffbits = charsToInt(4, &fileData[10]);
    int bcSize = charsToInt(4, &fileData[14]);
    if(bcSize == 40){  // Windows BMP
        imageData->width = charsToInt(4, &fileData[18]);
        imageData->height = charsToInt(4, &fileData[22]);
        imageData->bitCount = charsToInt(2, &fileData[28]);
        int compression = charsToInt(4, &fileData[30]);  // 圧縮形式
        int sizeImage = charsToInt(4, &fileData[34]);  // 画像データ部のサイズ
        int xPixPerMeter = charsToInt(4, &fileData[38]);  // 横方向解像度
        int yPixPerMeter = charsToInt(4, &fileData[42]);  // 縦方向解像度
        int clrUsed = charsToInt(4, &fileData[46]);  // 格納されているパレット数
        int cirImportant = charsToInt(4, &fileData[50]);  // 重要なパレットのインデックス

        // pixelDataの初期化
        int mod = imageData->width % 4;
        imageData->pixelDataLength = imageData->width * imageData->height;
        imageData->pixelData = new RGB[imageData->pixelDataLength];

        if(imageData->bitCount <= 8){
            // パレットデータ
            RGB* paletteData = new RGB[clrUsed];
            // パレットデータ取得
            for(int i = 0; i < clrUsed; i++){
                paletteData[i].B = fileData[54 + i * WINDOWS_PALETTE_SIZE];
                paletteData[i].G = fileData[55 + i * WINDOWS_PALETTE_SIZE];
                paletteData[i].R = fileData[56 + i * WINDOWS_PALETTE_SIZE];
                // OS/2だとAは存在しない
                paletteData[i].A = fileData[57 + i * WINDOWS_PALETTE_SIZE];
            }

            // pixel
            unsigned char paletteIndex = 0;
            int pixelIndex = 0;
            for(int i = 0; i < (imageData->pixelDataLength + mod * imageData->height); i++){
                // 4の倍数で割り切れない部分はスキップ
                if(i % (imageData->width + mod) >= imageData->width){
                    continue;
                }

                if(imageData->bitCount == 8){
                    paletteIndex = fileData[bfOffbits + i];
                } else if(imageData->bitCount == 4){
                    paletteIndex = fileData[bfOffbits + i / 2];
                    paletteIndex = paletteIndex << (i % 2 * 4);
                    paletteIndex = paletteIndex >> 4;
                } else if(imageData->bitCount == 1){
                    // TODO: bitが1の時だけおかしい
                    paletteIndex = fileData[bfOffbits + i / 4];
                    paletteIndex = paletteIndex << (i % 8);
                    paletteIndex = paletteIndex >> 7;
                } else {
                    printf("illegal bit count\n");
                    exit(EXIT_FAILURE);
                }

                imageData->pixelData[pixelIndex].R = paletteData[paletteIndex].R;
                imageData->pixelData[pixelIndex].G = paletteData[paletteIndex].G;
                imageData->pixelData[pixelIndex].B = paletteData[paletteIndex].B;
                imageData->pixelData[pixelIndex].A = paletteData[paletteIndex].A;
                pixelIndex++;
            }
            delete[] paletteData;
        } else {
            // pixel
            int bytePerPixel = (imageData->bitCount == 24) ? 3 : 4;
            int pixelIndex = 0;
            for(int i = 0; i < imageData->pixelDataLength + mod * imageData->height; i++){
                // 4の倍数で割り切れない部分はスキップ
                if(i % (imageData->width + mod) >= imageData->width){
                    continue;
                }

                imageData->pixelData[pixelIndex].B = fileData[bfOffbits + i * bytePerPixel];
                imageData->pixelData[pixelIndex].G = fileData[bfOffbits + 1 + i * bytePerPixel];
                imageData->pixelData[pixelIndex].R = fileData[bfOffbits + 2 + i * bytePerPixel];
                imageData->pixelData[pixelIndex].A = (imageData->bitCount == 24) ? 0 : fileData[bfOffbits + 3 + i * bytePerPixel];
                pixelIndex++;
            }
        }
    } else {  // OS/2 BMP
        // 情報ヘッダのbyteサイズや種類ががwindowsと異なるため別途対応が必要
        printf("OS/2 bitmapは非対応です。\n");
        exit(EXIT_FAILURE);
    }

    return imageData;
}

void BMP::generateImage(ImageData* data){
    // ファイルヘッダ
    unsigned char bfSize[4] = {0x0, 0x0, 0x0, 0x0};  // 適当
    char bfReserved1[2] = {0x0, 0x0};
    char bfReserved2[2] = {0x0, 0x0};
    unsigned char* bfOffBits = intToChars(4, 54);

    // 情報ヘッダ
    char bcSize[4] = {0x28, 0x0, 0x0, 0x0};
    unsigned char* bcWidth = intToChars(4, data->width);
    unsigned char* bcHeight = intToChars(4, data->height);
    char bcPlanes[2] = {0x1, 0x0};
    char bcBitCount[2] = {0x20, 0x0};
    char biCompression[4] = {0x0, 0x0, 0x0, 0x0};
    char biSizeImage[4] = {0x0, 0x0, 0x0, 0x0};  // 適当
    char biXPixPerMeter[4] = {0x0, 0x0, 0x0, 0x0};  // 適当
    char biYPixPerMeter[4] = {0x0, 0x0, 0x0, 0x0};  // 適当
    char biClrUsed[4] = {0x0, 0x0, 0x0, 0x0};
    char biCirImportant[4] = {0x0, 0x0, 0x0, 0x0};

    // ファイル
    FILE* file;
    char outputFilePath[260] = "";
    strcat(outputFilePath, this->filePath);
    strcat(outputFilePath, ".");
    strcat(outputFilePath, this->extension);
    if((file = fopen(outputFilePath, "wb")) == NULL){
        printf("file open error\n");
        exit(EXIT_FAILURE);
    }

    // ファイルヘッダ書き込み
    fwrite(this->fileSignature, 1, 2, file);
    fwrite(bfSize, 1, 4, file);
    fwrite(bfReserved1, 1, 2, file);
    fwrite(bfReserved2, 1, 2, file);
    fwrite(bfOffBits, 1, 4, file);

    // 情報ヘッダ書き込み
    fwrite(bcSize, 1, 4, file);
    fwrite(bcWidth, 1, 4, file);
    fwrite(bcHeight, 1, 4, file);
    fwrite(bcPlanes, 1, 2, file);
    fwrite(bcBitCount, 1, 2, file);
    fwrite(biCompression, 1, 4, file);
    fwrite(biSizeImage, 1, 4, file);
    fwrite(biXPixPerMeter, 1, 4, file);
    fwrite(biYPixPerMeter, 1, 4, file);
    fwrite(biClrUsed, 1, 4, file);
    fwrite(biCirImportant, 1, 4, file);

    // 画像データ書き込み
    int mod = data->width % 4;
    int pixelIndex = 0;
    for(int heightIndex = 0; heightIndex < data->height; heightIndex++){
        for(int widthIndex = 0; widthIndex < data->width; widthIndex++){
            pixelIndex = widthIndex + (data->width * heightIndex);
            fwrite(&data->pixelData[pixelIndex].B, 1, 1, file);
            fwrite(&data->pixelData[pixelIndex].G, 1, 1, file);
            fwrite(&data->pixelData[pixelIndex].R, 1, 1, file);
            fwrite(&data->pixelData[pixelIndex].A, 1, 1, file);
        }

        for(int modIndex = 0; modIndex < mod; modIndex++){
            printf("test");
            fwrite(0, 1, 1, file);
        }
    }

    fclose(file);

    printf("image saved in %s\n", outputFilePath);
}
