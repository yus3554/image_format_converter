#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image/Image.h"
#include "converter/Converter.h"

#define MAX_FILE_PATH_LENGTH 256

void analyzeArgs(char* imagePath, ImageFormat& convertFormat, int argc, char* argv[]);

int main(int argc, char* argv[]){
    // 変換フォーマット
    ImageFormat convertFormat = ImageFormat::PNG;
    // 画像パス
    char imagePath[MAX_FILE_PATH_LENGTH] = "";

    // 画像パスとフォーマットをコマンドライン引数から取得
    analyzeArgs(imagePath, convertFormat, argc, argv);

    printf("format:\t%d\n", convertFormat);
    printf("path:\t%s\n", imagePath);

    Converter *c = new Converter(imagePath, convertFormat);
    c->printImageFilePath();
    delete c;

    return 0;
}

void analyzeArgs(char* imagePath, ImageFormat& convertFormat, int argc, char* argv[]){
    for (int i = 1; i < argc; i++){
        // フォーマット
        if(strcmp(argv[i], "-f") == 0 && ((i + 1) < argc)){
            if (strcmp(argv[i + 1], "bmp") == 0){
                convertFormat = ImageFormat::BMP;
            } else if(strcmp(argv[i + 1], "png") == 0){
                convertFormat = ImageFormat::PNG;
            } else {
                printf("%s は対応していない画像フォーマットです。\n", argv[i + 1]);
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

