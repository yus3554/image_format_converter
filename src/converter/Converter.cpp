/**
 * @file Converter.cpp
 * @author Yusuke Ota
 * @brief 画像フォーマットを変換するクラスの実装部
 * @version 0.1
 * @date 2024-01-02
 */

#include <stdio.h>
#include "Converter.h"
#include "../image/Image.h"

Converter::Converter(char* imagePath, ImageFormat format){
    this->imagePath         = imagePath;
    this->format            = format;

    // ファクトリーから適切な画像クラスを取得
    ImageFactory factory    = ImageFactory();
    this->image             = factory.createImage(imagePath);
}

Converter::~Converter(){
    delete this->image;
}

void Converter::printImageFilePath(){
    this->image->printFileName();
}
