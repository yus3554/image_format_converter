/**
 * @file RGB.cpp
 * @author Yusuke Ota
 * @brief RGBクラスの実装部
 * @version 0.3
 * @date 2024-04-15
 */

#include "Image.h"

void RGB::toString(){
    printf("%02x %02x %02x %02x\n", this->R, this->G, this->B, this->A);
}
