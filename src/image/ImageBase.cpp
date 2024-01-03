/**
 * @file ImageBase.cpp
 * @author Yusuke Ota
 * @brief 画像基底クラスの実装部
 * @version 0.1
 * @date 2024-01-02
 */

#include <stdio.h>
#include <stdlib.h>
#include "Image.h"


ImageBase::ImageBase(){}

ImageBase::ImageBase(const char filePath[]){
    this->filePath = filePath;
}

void ImageBase::filePathNullCheck(){
    if(this->filePath == NULL){
        printf("filePathがNULLです。\n");
        exit(EXIT_FAILURE);
    }
}

void ImageBase::printFileName(){
    printf("%s\n", this->filePath);
}

ImageData ImageBase::getImageData(){
    // 各画像クラスで初期化してください。
    return ImageData();
}

void ImageBase::generateImage(ImageData data){
    // 各画像クラスで初期化してください。
}
