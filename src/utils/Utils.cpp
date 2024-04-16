/**
 * @file Utils.cpp
 * @author Yusuke Ota
 * @brief ユーティリティ関数の実装
 * @version 0.3
 * @date 2024-04-15
 */

#include "utils.h"

void printCharsToHex(int charLength, unsigned char* chars){
    for(int i = 0; i < charLength; i++){
        printf("%02x ", chars[i]);
    }
    printf("\n");
}

int charsToInt(int charLength, unsigned char* chars, bool isLittleEndian){
    int result = 0;
    for(int i = 0; i < charLength; i++){
        if(isLittleEndian){
            result = result + chars[i] * (int)pow(16, i * 2);
        } else {
            result = result + chars[i] * (int)pow(16, (charLength - i - 1) * 2);
        }
    }
    return result;
}

unsigned char* intToChars(int charLength, unsigned int num){
    unsigned char* result = new unsigned char[charLength];
    unsigned int twoByteF = 255;

    for(int i = 0; i < charLength; i++){
        result[i] = (int)((num & (twoByteF << (8 * i))) >> (8 * i));
    }

    return result;
}

int getFileSize(const char* filePath){
    FILE* file;
    if((fopen_s(&file, filePath, "rb")) != 0){
        printf("file open error\n");
        exit(EXIT_FAILURE);
    }
    // ファイルサイズ
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    if(fileSize < 14){
        printf("file size error\n");
        exit(EXIT_FAILURE);
    }
    return fileSize;
}
