/**
 * 画像基底クラスの実装ファイル
*/
#include "Image.h"

ImageBase::ImageBase(){}
ImageBase::ImageBase(const char filePath[]){
    this->filePath = filePath;
    
    this->judgeCollectFile();
}
void ImageBase::printFileName(){
    if(this->filePath == NULL){
        return;
    }
    printf("file path is %s .", this->filePath);
}
void ImageBase::open(const char filePath[]){
    if(filePath == NULL){
        return;
    }
    this->filePath = filePath;
}
void ImageBase::create(){
    return;
}
void ImageBase::save(const char saveFilePath[]){
    return;
}
void ImageBase::judgeCollectFile(){
    if(this->filePath == NULL){
        return;
    }
    // ファイルを読んで正しい画像ファイルか判定
    this->isCorrectFile = true;
}
