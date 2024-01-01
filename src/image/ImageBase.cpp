/**
 * 画像基底クラスの実装ファイル
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
