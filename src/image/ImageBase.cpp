/**
 * @file ImageBase.cpp
 * @author Yusuke Ota
 * @brief 画像基底クラスの実装部
 * @version 0.3
 * @date 2024-04-15
 */

#include "Image.h"


ImageBase::ImageBase(){
    this->filePath = "";
    this->format = ImageFormat::OTHERS;

}

ImageBase::ImageBase(const char filePath[]){
    this->filePath = filePath;
    this->format = ImageFormat::OTHERS;
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

ImageData* ImageBase::getImageData(){
    // 各画像クラスで初期化してください。
    return new ImageData();
}

void ImageBase::generateImage(ImageData* data){
    // 各画像クラスで初期化してください。
}
