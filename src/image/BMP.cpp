/**
 * @file BMP.cpp
 * @author Yusuke Ota
 * @brief BMPクラスの実装部
 * @version 0.1
 * @date 2024-01-02
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Image.h"

BMP::BMP(const char filePath[]){
    this->filePath = filePath;
    printf("bmp instance\n");
}

const unsigned char BMP::fileSignature[2] = {0x42, 0x4d};

const char BMP::extension[4] = "bmp";



void printChars(int charLength, char* chars){
    for(int i = 0; i < charLength; i++){
        printf("%02x ", chars[i]);
    }
    printf("\n");
}

/**
 * @brief char配列を逆にして16進数としてintに変換
 * 
 * @param charLength 
 * @param chars 
 * @return int 
 */
int charsToInt(int charLength, char* chars){
    int result = 0;
    for(int i = charLength - 1; i >= 0; i--){
        result = result + chars[i] * pow(16, i * 2);
    }
    return result;
}


ImageData BMP::getImageData(){
    this->filePathNullCheck();

    // ファイルヘッダ
    char bfSize[4];  // ファイルサイズ
    char bfOffBits[4];  // ファイル先頭から画像データまでのオフセット

    // 情報ヘッダ
    char bcSize[4];  // ヘッダサイズ
    char bcWidth[4];  // 幅
    char bcHeight[4];  // 高さ
    char bcBitCount[2];  // 1画素あたりのデータサイズ
    char biCompression[4];  // 圧縮形式
    char biSizeImage[4];  // 画像データ部のサイズ
    char biXPixPerMeter[4];  // 横方向解像度
    char biYPixPerMeter[4];  // 縦方向解像度
    char biClrUsed[4];  // 格納されているパレット数
    char biCirImportant[4];  // 重要なパレットのインデックス

    // パレットデータ
    char* paletteData;

    // 画像データ
    char* pixelData;
    
    // ファイル解析
    FILE* file;
    if((file = fopen(filePath, "rb")) == NULL){
        printf("file open error\n");
        exit(EXIT_FAILURE);
    }
    // ファイルヘッダ取得
    fseek(file, 2, SEEK_SET);
    fread(bfSize, 1, sizeof(bfSize), file);
    fseek(file, 4, SEEK_CUR);
    fread(bfOffBits, 1, sizeof(bfOffBits), file);

    // ピクセルデータの初期化
    int pixelDataLength = charsToInt(4, bfSize) - charsToInt(4, bfOffBits);
    pixelData = new char[pixelDataLength];

    // 情報ヘッダ取得
    fread(bcSize, 1, sizeof(bcSize) / sizeof(*bcSize), file);
    if(charsToInt(4, bcSize) == 40){  // Windows BMP
        fread(bcWidth, 1, sizeof(bcWidth), file);
        fread(bcHeight, 1, sizeof(bcHeight), file);
        fseek(file, 2, SEEK_CUR);
        fread(bcBitCount, 1, sizeof(bcBitCount), file);
        fread(biCompression, 1, sizeof(biCompression), file);
        fread(biSizeImage, 1, sizeof(biSizeImage), file);
        fread(biXPixPerMeter, 1, sizeof(biXPixPerMeter), file);
        fread(biYPixPerMeter, 1, sizeof(biYPixPerMeter), file);
        fread(biClrUsed, 1, sizeof(biClrUsed), file);
        fread(biCirImportant, 1, sizeof(biCirImportant), file);

        // パレット取得
        if(charsToInt(2, bcBitCount) <= 8){
            int paletteDataLength = charsToInt(4, biClrUsed) * 4;
            paletteData = new char[paletteDataLength];  // Windowsは4byte、os/2は3byte
            fread(paletteData, 1, paletteDataLength, file);
        }
    } else {  // OS/2 BMP
        // 情報ヘッダのbyteサイズや種類ががwindowsと異なるため別途対応が必要
        printf("OS/2 bitmapは非対応です。\n");
        exit(EXIT_FAILURE);
    }
    // ピクセルデータ取得
    fseek(file, charsToInt(4, bfOffBits), SEEK_SET);
    fread(pixelData, 1, pixelDataLength, file);
    fclose(file);

    // ImageDataクラスに格納


    printf("%d\n", charsToInt(4, biClrUsed));
    printChars(16, paletteData);
    printChars(4, pixelData);

    return ImageData();
}

void BMP::generateImage(ImageData data){
    // 各画像クラスで初期化してください。
}
