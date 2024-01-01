/**
 * コンバータークラスの実装
*/
#include <stdio.h>
#include "Converter.h"
#include "../image/Image.h"

Converter::Converter(char* imagePath, ImageFormat format){
    this->imagePath         = imagePath;
    this->format            = format;

    ImageFactory factory    = ImageFactory();
    this->image             = factory.createImage(imagePath);
}
Converter::~Converter(){
    delete this->image;
}
void Converter::printImageFilePath(){
    this->image->printFileName();
}