/**
 * BMPクラスの実装
*/
#include "Image.h"

BMP::BMP(){}
BMP::BMP(const char filePath[]){
    this->filePath = filePath;
    printf("bmp instance\n");
}
const unsigned char BMP::fileSignature[2] = {0x42, 0x4d};
