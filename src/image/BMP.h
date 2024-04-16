/**
 * @file BMP.h
 * @author Yusuke Ota
 * @brief BMPに関わるクラス・構造体・列挙型の宣言部
 * @version 0.3
 * @date 2024-04-15
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Image.h"
#include "../utils/Utils.h"

/**
 * @brief BMPクラス
 * 
 */
class BMP : public ImageBase{
private:
    /**
     * @brief オリジナルの画像ファイルのヘッダー情報を格納する構造体
     * 
     */
    struct OriginalHeader
    {
        /**
         * @brief ファイルサイズ（実データ情報）
         * 
         */
        int fileSize;

        /**
         * @brief 圧縮形式
         * 
         */
        int compression;

        /**
         * @brief 画像データ部のサイズ
         * 
         */
        int sizeImage;

        /**
         * @brief 横方向解像度
         * 
         */
        int xPixPerMeter;

        /**
         * @brief 縦方向解像度
         * 
         */
        int yPixPerMeter;

        /**
         * @brief 格納されているパレット数
         * 
         */
        int clrUsed;

        /**
         * @brief 重要なパレットのインデックス
         * 
         */
        int cirImportant;

        /**
         * @brief ファイル先頭から画像データまでのオフセット
         * 
         */
        int bfOffbits;

        /**
         * @brief ファイルサイズ（ヘッダー情報）
         * 
         */
        int bcSize;

        /**
         * @brief 横幅のバイト数
         * 
         */
        int widthByte;

        /**
         * @brief 横幅のバイト数を4の倍数になるように修正したバイト数
         * 
         */
        int widthByteIncludeMod;
    };

    /**
     * @brief オリジナルの画像のヘッダの構造体
     * 
     */
    OriginalHeader* origHeader;

    /**
     * @brief 画像ファイルからデータを読み込む。
     *
     * @param fileData ファイルのデータを格納したい変数
     */
    void readFile(unsigned char* fileData);

    /**
     * @brief Windows BMPのヘッダーを読み込む。（bitCount <= 8）
     *
     * @param imageData 読み込んだ一部のヘッダデータを格納したい変数
     * @param fileData 読み込むファイルデータ
     */
    void readWinBMPHeader(ImageData* imageData, unsigned char* fileData);

    /**
     * @brief Windows BMPのパレット情報を読み込む。
     *
     * @param imageData 読み込んだ画像データを格納したい変数
     * @param fileData 読み込むファイルデータ
     *
     */
    void readWinBMPPallete(ImageData* imageData, unsigned char* fileData);

    /**
     * @brief Windows BMPのRGB情報を読み込む。（bitCount > 8）
     *
     * @param imageData 読み込んだ画像データを格納したい変数
     * @param fileData 読み込むファイルデータ
     *
     */
    void readWinBMPRGB(ImageData* imageData, unsigned char* fileData);

public:
    /**
     * @brief BMPのファイルシグネチャ
     *
     */
    static const unsigned char  fileSignature[2];

    /**
     * @brief BMPの拡張子名
     *
     */
    static const char           extension[4];

    /**
     * @brief Construct a new BMP object
     *
     * @param filePath 画像ファイルパス
     */
    BMP(const char filePath[]);

    /**
     * @brief Get the Image Data object
     *
     * @return ImageData*
     */
    ImageData*   getImageData();

    /**
     * @brief 画像を生成する
     *
     * @param data 生成したい画像データ
     */
    void        generateImage(ImageData* data);
};
