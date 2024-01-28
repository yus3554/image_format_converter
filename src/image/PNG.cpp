/**
 * @file PNG.cpp
 * @author Yusuke Ota
 * @brief PNGクラスの実装部
 * @version 0.1
 * @date 2024-01-02
 */

#include <stdlib.h>
#include <string.h>
#include "Image.h"
#include "../utils/Utils.h"

PNG::PNG(const char filePath[]){
    this->filePath = filePath;
}

const unsigned char PNG::fileSignature[8] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

const char PNG::extension[4] = "png";

ImageData* PNG::getImageData(){
    this->filePathNullCheck();

    // ファイルサイズ
    int fileSize = 0;

    // ImageDataに格納
    ImageData* imageData = new ImageData();

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

    int chunkDataLength= 0;
    unsigned char chunkDataLengthChar[4];
    char chunkType[4];

    // IHDR
    fseek(file, 8, SEEK_SET);
    fread(&chunkDataLengthChar, 1, 4, file);
    chunkDataLength = charsToInt(4, chunkDataLengthChar, false);
    fread(chunkType, 1, 4, file);
    // printf("%d %s\n", chunkDataLength, chunkType);
    if(strcmp(chunkType, "IHDR") != 0 || chunkDataLength != 13){
        printf("illegal file.\n");
        exit(EXIT_FAILURE);
    }
    unsigned char* ihdrData = new unsigned char[chunkDataLength];
    fread(ihdrData, 1, chunkDataLength, file);
    fseek(file, 4, SEEK_CUR);  // CRC
    imageData->width = charsToInt(4, &ihdrData[0], false);
    imageData->height = charsToInt(4, &ihdrData[4], false);
    imageData->bitCount = ihdrData[8];
    int colorType = ihdrData[9];
    int compression = ihdrData[10];
    int filter = ihdrData[11];
    int interlace = ihdrData[12];
    printf("width: %d, height: %d, bitCount: %d, colorType: %d, compression:%d, filter: %d\n", imageData->width, imageData->height, imageData->bitCount, colorType, compression, filter);
    delete ihdrData;

    // PLTE, IDATの取得
    bool plte = false;
    RGB* palettes;
    unsigned char* idatData;
    while(true){
        if(ftell(file) > fileSize){
            printf("illegal file.\n");
            exit(EXIT_FAILURE);
        }

        fread(&chunkDataLengthChar, 1, 4, file);
        chunkDataLength = charsToInt(4, chunkDataLengthChar, false);
        fread(chunkType, 1, 4, file);

        if(strcmp(chunkType, "PLTE") == 0){
            plte = true;
            if(chunkDataLength % 3 != 0){
                printf("illegal file.\n");
                exit(EXIT_FAILURE);
            }

            palettes = new RGB[chunkDataLength / 3];
            for(int paletteIndex = 0; paletteIndex < chunkDataLength / 3; paletteIndex++){
                fread(&palettes[paletteIndex].R, 1, 1, file);
                fread(&palettes[paletteIndex].G, 1, 1, file);
                fread(&palettes[paletteIndex].B, 1, 1, file);
                palettes[paletteIndex].A = 0;
            }
            fseek(file, 4, SEEK_CUR);  // CRC
        } else if (strcmp(chunkType, "IDAT") == 0){
            if(colorType == 3 && !plte){
                printf("illegal file.\n");
                exit(EXIT_FAILURE);
            }
            idatData = new unsigned char[chunkDataLength];
            fread(idatData, 1, chunkDataLength, file);
            fseek(file, 4, SEEK_CUR);  // CRC
            printf("%d\n", chunkDataLength);  // zlibで圧縮されているため、pixel数と異なる
        } else if (strcmp(chunkType, "IEND") == 0){
            break;
        } else {
            // other chunk
            // printf("other chunk: %s\n", chunkType);
            fseek(file, chunkDataLength, SEEK_CUR);
            fseek(file, 4, SEEK_CUR);  // CRC
        }
    }

    // IDATのRGB化
    imageData->pixelDataLength = imageData->width * imageData->height;
    imageData->rgbPixelData = new RGB[imageData->pixelDataLength];
    // idatDataを解凍しないといけない
    if(plte){
    }

    return new ImageData();
}

void PNG::generateImage(ImageData* data){
    // 各画像クラスで初期化してください。
}
