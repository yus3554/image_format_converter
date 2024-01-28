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
#include "../utils/Utils.h"

#define WINDOWS_PALETTE_SIZE 4

BMP::BMP(const char filePath[]){
    this->filePath = filePath;
}

const unsigned char BMP::fileSignature[2] = {0x42, 0x4d};

const char BMP::extension[4] = "bmp";

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
    int bfOffbits = charsToInt(4, &fileData[10], true);
    int bcSize = charsToInt(4, &fileData[14], true);
    if(bcSize == 40){  // Windows BMP
        imageData->width = abs(charsToInt(4, &fileData[18], true));
        imageData->height = abs(charsToInt(4, &fileData[22], true));
        imageData->bitCount = charsToInt(2, &fileData[28], true);
        int compression = charsToInt(4, &fileData[30], true);  // 圧縮形式
        int sizeImage = charsToInt(4, &fileData[34], true);  // 画像データ部のサイズ
        int xPixPerMeter = charsToInt(4, &fileData[38], true);  // 横方向解像度
        int yPixPerMeter = charsToInt(4, &fileData[42], true);  // 縦方向解像度
        int clrUsed = charsToInt(4, &fileData[46], true);  // 格納されているパレット数
        int cirImportant = charsToInt(4, &fileData[50], true);  // 重要なパレットのインデックス

        // pixelDataの初期化
        imageData->pixelDataLength = abs(imageData->width * imageData->height);
        
        // 横幅が4の倍数byteになる必要があるため、mod(余り)を追加
        int widthByte = imageData->width * imageData->bitCount / 8;
        int mod = (4 - (widthByte % 4)) % 4;
        int widthByteIncludeMod = widthByte + mod;
        // modを含めたpixelのbyte
        int pixelNumIncludeMod = imageData->pixelDataLength + (mod * imageData->height * imageData->bitCount / 8);

        // pixelのbyte数とファイルbyte数の比較
        int pixelByte = 0;
        if (imageData->bitCount > 8){
            pixelByte = imageData->pixelDataLength / imageData->bitCount + mod * imageData->height;
        } else {
            pixelByte = imageData->pixelDataLength / (8 / imageData->bitCount) + mod * imageData->height;
        }
        if(fileSize < (pixelNumIncludeMod * imageData->bitCount / 8 + bfOffbits)){
            printf("file size error or file width and height error\n");
            exit(EXIT_FAILURE);
        }

        if(imageData->bitCount <= 8){
            imageData->isPalette = true;
            imageData->palettePixelData = new unsigned char[imageData->pixelDataLength];

            // パレットデータ
            imageData->paletteLength = clrUsed;
            imageData->paletteData = new RGB[imageData->paletteLength];
            // パレットデータ取得
            for(int i = 0; i < clrUsed; i++){
                imageData->paletteData[i].B = fileData[54 + i * WINDOWS_PALETTE_SIZE];
                imageData->paletteData[i].G = fileData[55 + i * WINDOWS_PALETTE_SIZE];
                imageData->paletteData[i].R = fileData[56 + i * WINDOWS_PALETTE_SIZE];
                // OS/2だとAは存在しない
                imageData->paletteData[i].A = fileData[57 + i * WINDOWS_PALETTE_SIZE];
            }

            // pixel
            unsigned char paletteIndex = 0;
            int pixelIndex = 0;
            for(int i = 0; i < fileSize - bfOffbits; i++){
                // 横幅のbyteが4の倍数を超える場合にスキップ
                if(i % widthByteIncludeMod >= widthByte){
                    continue;
                }

                switch (imageData->bitCount){
                case 8:
                    paletteIndex = fileData[bfOffbits + i];
                    imageData->palettePixelData[pixelIndex] = paletteIndex;
                    pixelIndex++;
                    break;
                case 4:
                    for(int j = 0; j < 2; j++){
                        paletteIndex = fileData[bfOffbits + i];
                        paletteIndex = paletteIndex << (j % 2 * 4);
                        paletteIndex = paletteIndex >> 4;
                        imageData->palettePixelData[pixelIndex] = paletteIndex;
                        pixelIndex++;
                    }
                    break;
                case 1:
                    for(int j = 0; j < 8; j++){
                        paletteIndex = fileData[bfOffbits + i];
                        paletteIndex = paletteIndex << (j % 8);
                        paletteIndex = paletteIndex >> 7;
                        imageData->palettePixelData[pixelIndex] = paletteIndex;
                        pixelIndex++;
                    }
                    break;
                default:
                    break;
                }
            }
        } else {
            imageData->isPalette = false;
            imageData->rgbPixelData = new RGB[imageData->pixelDataLength];

            // pixel
            int pixelIndex = 0;
            int rgbaIndex = 0;
            unsigned char colorValue = 0;
            for(int i = 0; i < fileSize - bfOffbits; i++){
                // 横幅のbyteが4の倍数を超える場合にスキップ
                if(i % widthByteIncludeMod >= widthByte){
                    continue;
                }

                switch (imageData->bitCount){
                case 32:
                    switch (rgbaIndex){
                    case 0:
                        imageData->rgbPixelData[pixelIndex].B = fileData[bfOffbits + i];
                        rgbaIndex++;
                        break;
                    case 1:
                        imageData->rgbPixelData[pixelIndex].G = fileData[bfOffbits + i];
                        rgbaIndex++;
                        break;
                    case 2:
                        imageData->rgbPixelData[pixelIndex].R = fileData[bfOffbits + i];
                        rgbaIndex++;
                        break;
                    case 3:
                        imageData->rgbPixelData[pixelIndex].A = fileData[bfOffbits + i];
                        rgbaIndex = 0;
                        pixelIndex++;
                        break;
                    default:
                        break;
                    }
                    break;
                case 24:
                    switch (rgbaIndex){
                    case 0:
                        imageData->rgbPixelData[pixelIndex].B = fileData[bfOffbits + i];
                        rgbaIndex++;
                        break;
                    case 1:
                        imageData->rgbPixelData[pixelIndex].G = fileData[bfOffbits + i];
                        rgbaIndex++;
                        break;
                    case 2:
                        imageData->rgbPixelData[pixelIndex].R = fileData[bfOffbits + i];
                        imageData->rgbPixelData[pixelIndex].A = 0;
                        rgbaIndex = 0;
                        pixelIndex++;
                        break;
                    default:
                        break;
                    }
                    break;
                case 16:
                    colorValue = fileData[bfOffbits + i];

                    switch (rgbaIndex){
                    case 0:
                        imageData->rgbPixelData[pixelIndex].B = colorValue & 0x7c >> 2;
                        imageData->rgbPixelData[pixelIndex].G = (colorValue & 0x3) << 3;
                        rgbaIndex++;
                        break;
                    case 1:
                        imageData->rgbPixelData[pixelIndex].G = imageData->rgbPixelData[pixelIndex].G | ((colorValue & 0xe0) >> 5);
                        imageData->rgbPixelData[pixelIndex].R = colorValue & 0x1f;
                        imageData->rgbPixelData[pixelIndex].A = 0;

                        // 値を8bitに変換
                        imageData->rgbPixelData[pixelIndex].R = (unsigned char)((float)0xff / (float)0x1f * imageData->rgbPixelData[pixelIndex].R);
                        imageData->rgbPixelData[pixelIndex].G = (unsigned char)((float)0xff / (float)0x1f * imageData->rgbPixelData[pixelIndex].G);
                        imageData->rgbPixelData[pixelIndex].B = (unsigned char)((float)0xff / (float)0x1f * imageData->rgbPixelData[pixelIndex].B);

                        rgbaIndex = 0;
                        pixelIndex++;
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
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
    int paletteIndex = 0;
    if(data->isPalette){
        // palette
        for(int heightIndex = 0; heightIndex < data->height; heightIndex++){
            for(int widthIndex = 0; widthIndex < data->width; widthIndex++){
                pixelIndex = widthIndex + (data->width * heightIndex);
                paletteIndex = data->palettePixelData[pixelIndex];
                fwrite(&data->paletteData[paletteIndex].B, 1, 1, file);
                fwrite(&data->paletteData[paletteIndex].G, 1, 1, file);
                fwrite(&data->paletteData[paletteIndex].R, 1, 1, file);
                fwrite(&data->paletteData[paletteIndex].A, 1, 1, file);
            }

            for(int modIndex = 0; modIndex < mod; modIndex++){
                printf("test");
                fwrite(0, 1, 1, file);
            }
        }
    } else {
        // rgb
        for(int heightIndex = 0; heightIndex < data->height; heightIndex++){
            for(int widthIndex = 0; widthIndex < data->width; widthIndex++){
                pixelIndex = widthIndex + (data->width * heightIndex);
                fwrite(&data->rgbPixelData[pixelIndex].B, 1, 1, file);
                fwrite(&data->rgbPixelData[pixelIndex].G, 1, 1, file);
                fwrite(&data->rgbPixelData[pixelIndex].R, 1, 1, file);
                fwrite(&data->rgbPixelData[pixelIndex].A, 1, 1, file);
            }

            for(int modIndex = 0; modIndex < mod; modIndex++){
                printf("test");
                fwrite(0, 1, 1, file);
            }
        }
    }

    fclose(file);

    printf("image saved in %s\n", outputFilePath);
}
