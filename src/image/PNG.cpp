/**
 * @file PNG.cpp
 * @author Yusuke Ota
 * @brief PNGクラスの実装部
 * @version 0.1
 * @date 2024-01-02
 */

#include "Image.h"

PNG::PNG(const char filePath[]){
    this->filePath = filePath;
    printf("png instance\n");
}

const unsigned char PNG::fileSignature[8] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

const char PNG::extension[4] = "png";
