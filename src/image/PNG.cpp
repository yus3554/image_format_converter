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

    // IHDR
    int ihdrSize = charsToInt(4, &fileData[8], false);
    unsigned char* ihdrChunkType = &fileData[12];
    printf("%02x\n", ihdrChunkType[0]);
    if(ihdrChunkType[0] != 0x49 || ihdrChunkType[1] != 0x48 || ihdrChunkType[2] != 0x44 || ihdrChunkType[3] != 0x52){
        printf("illegal ihdr chunk\n");
        exit(EXIT_FAILURE);
    }
    imageData->width = abs(charsToInt(4, &fileData[16], false));
    imageData->height = abs(charsToInt(4, &fileData[20], false));
    int bitDepth = fileData[24];
    int colorType = fileData[25];
    int compression = fileData[26];
    int filter = fileData[27];
    int interlace = fileData[28];
    unsigned char* ihdrCRC = &fileData[29];
    printf("width: %d, height: %d\n", imageData->width, imageData->height);
    printf("bitDepth: %d, colorType: %d, compression: %d, filter: %d, interlace: %d\n", bitDepth, colorType, compression, filter, interlace);

    // PLTE or IDAT
    int ihdrIndex = 33;
    int plteOrIdatSize = charsToInt(4, &fileData[ihdrIndex], false);
    unsigned char* plteOrIdatChunkType = &fileData[ihdrIndex + 4];
    printCharsToHex(4, plteOrIdatChunkType);
    if(plteOrIdatChunkType[0] == 0x50 && plteOrIdatChunkType[1] == 0x4c && plteOrIdatChunkType[2] == 0x54 && plteOrIdatChunkType[3] == 0x45){
        // PLTE

    } else if(plteOrIdatChunkType[0] == 0x49 && plteOrIdatChunkType[1] == 0x44 && plteOrIdatChunkType[2] == 0x41 && plteOrIdatChunkType[3] == 0x54){
        // IDAT
        if(colorType == 3){
            printf("plte not exists.\n");
            exit(EXIT_FAILURE);
        }

    } else {
        // OTHERS
        printf("unsupported file.\n");
        exit(EXIT_FAILURE);
    }

    return new ImageData();
}

void PNG::generateImage(ImageData* data){
    // 各画像クラスで初期化してください。
}
