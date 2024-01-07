/**
 * @file Utils.cpp
 * @author Yusuke Ota
 * @brief ユーティリティ関数の実装
 * @version 0.1
 * @date 2024-01-06
 */

#include <stdio.h>
#include <math.h>

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
            result = result + chars[i] * pow(16, i * 2);
        } else {
            result = result + chars[i] * pow(16, (charLength - i - 1) * 2);
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
