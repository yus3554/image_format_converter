/**
 * @file ImageFactory.cpp
 * @author Yusuke Ota
 * @brief 画像クラスのファクトリークラスの実装部
 * @version 0.1
 * @date 2024-01-02
 */

#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "ImageFactory.h"

/**
 * @brief 取得するファイルシグネチャ長
 * 
 */
#define SIGNATURE_SIZE 8

ImageFormat ImageFactory::judgeImageFormat(char* filePath){
    // ファイルシグネチャ用変数
    unsigned char signature[SIGNATURE_SIZE];

    // ファイルのヘッダを取得
    FILE* file;
    if((file = fopen(filePath, "rb")) == NULL){
        printf("file open error\n");
        exit(EXIT_FAILURE);
    }
    fread(signature, sizeof(*signature), SIGNATURE_SIZE, file);
    fclose(file);

    // ヘッダから画像フォーマットを判定
    if(ImageFactory::isCorrectFileSignature(
        SIGNATURE_SIZE, signature, sizeof(BMP::fileSignature) / sizeof(char), BMP::fileSignature
    )){
        return ImageFormat::BMP;
    } else if(ImageFactory::isCorrectFileSignature(
        SIGNATURE_SIZE, signature, sizeof(PNG::fileSignature) / sizeof(char), PNG::fileSignature
    )){
        return ImageFormat::PNG;
    } else {
        return ImageFormat::OTHERS;
    }
}

bool ImageFactory::isCorrectFileSignature(
    int srcSigSize, unsigned char* srcSig, int destSigSize, const unsigned char* destSig
){
    bool result = true;

    // destを基準に比較するので、destよりもsrcが小さい場合はfalse
    if(srcSigSize < destSigSize){
        return false;
    }

    // 比較
    for(int i = 0; i < destSigSize; i++){
        if(srcSig[i] != destSig[i]){
            result = false;
            break;
        }
    }

    return result;
}

IImage* ImageFactory::createImageFromPath(char* filePath){
    ImageFormat format = this->judgeImageFormat(filePath);

    return this->createImageFromFormat(format, filePath);
}

IImage* ImageFactory::createImageFromFormat(ImageFormat format, char* filePath){
    if(format == ImageFormat::BMP){
        return new BMP(filePath);
    } else if (format == ImageFormat::PNG){
        return new PNG(filePath);
    } else {
        printf("対応していないファイルです。\n");
        exit(EXIT_FAILURE);
    }
}
