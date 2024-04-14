/**
 * @file Converter.cpp
 * @author Yusuke Ota
 * @brief 画像フォーマットを変換するクラスの実装部
 * @version 0.3
 * @date 2024-04-15
 */

#include "Converter.h"

Converter::Converter(char* imagePath, ImageFormat convertFormat){
    this->imagePath         = imagePath;
    this->convertFormat     = convertFormat;

    // ファクトリーから適切な画像クラスを取得
    this->factory           = new ImageFactory();
    this->image             = this->factory->createImageFromPath(imagePath);
}

Converter::~Converter(){
    delete this->image;
    delete this->factory;
}

void Converter::printImageFilePath(){
    this->image->printFileName();
}

void Converter::executeConvert(){
    // 出力用の画像クラスを生成
    IImage* exportImage = this->factory->createImageFromFormat(this->convertFormat, this->imagePath);

    // 画像データを取得
    ImageData* data = this->image->getImageData();

    // 画像を出力
    exportImage->generateImage(data);

    // 画像データを消去
    delete data;
}
