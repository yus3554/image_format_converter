/**
 * @file main.cpp
 * @author Yusuke Ota
 * @brief image_format_converterのメイン関数
 * @version 0.1
 * @date 2024-01-02
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image/Image.h"
#include "image/BMP.h"
#include "image/PNG.h"
#include "converter/Converter.h"

/**
 * @brief ファイルパスの最大長
 */
#define MAX_FILE_PATH_LENGTH 256

/**
 * @brief コマンドライン引数から画像パスと変換したい画像フォーマットを取得する
 * 
 * @param[out] imagePath 画像パスを格納するポインタ
 * @param[out] convertFormat 画像フォーマットを出力するポインタ
 * @param[in] argc コマンドライン引数の数
 * @param[in] argv コマンドライン引数
 */
void analyzeArgs(char* imagePath, ImageFormat& convertFormat, int argc, char* argv[]);

/**
 * @brief メイン関数
 */
int main(int argc, char* argv[]){
    // 変換フォーマット
    ImageFormat convertFormat = ImageFormat::PNG;
    // 画像パス
    char imagePath[MAX_FILE_PATH_LENGTH] = "";

    // 画像パスとフォーマットをコマンドライン引数から取得
    analyzeArgs(imagePath, convertFormat, argc, argv);

    // 変換を実行
    Converter *c = new Converter(imagePath, convertFormat);
    c->executeConvert();
    delete c;

    return 0;
}

void analyzeArgs(char* imagePath, ImageFormat& convertFormat, int argc, char* argv[]){
    for (int i = 1; i < argc; i++){
        // フォーマット
        if(strcmp(argv[i], "-f") == 0 && ((i + 1) < argc)){
            if (strcmp(argv[i + 1], BMP::extension) == 0){
                convertFormat = ImageFormat::BMP;
            } else if(strcmp(argv[i + 1], PNG::extension) == 0){
                convertFormat = ImageFormat::PNG;
            } else {
                printf("%s は対応していない出力フォーマットです。\n", argv[i + 1]);
                exit(EXIT_FAILURE);
            }
            // -fのあとは画像フォーマット文字列が入っているためスキップ
            i = i + 1;

        // 画像パス
        } else {
            // 初期化されていたらスキップ
            if(strcmp(imagePath, "") != 0)
                continue;

            if(strlen(argv[i]) < MAX_FILE_PATH_LENGTH){
                strcpy(imagePath, argv[i]);
            } else {
                printf("ファイルパス長が%d文字を超えています。", MAX_FILE_PATH_LENGTH);
                exit(EXIT_FAILURE);
            }
        }
    }
}

