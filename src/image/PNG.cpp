/**
 * PNGクラスの実装
*/
#include "Image.h"

#define PNG_FILE_SIGNATURE 8

PNG::PNG(){}
PNG::PNG(const char filePath[]){
    this->filePath = filePath;
    printf("png instance\n");
}
const unsigned char PNG::fileSignature[8] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
