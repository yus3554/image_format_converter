/**
 * @file Converter.h
 * @author Yusuke Ota
 * @brief 画像フォーマットを変換するクラスの宣言部
 * @version 0.1
 * @date 2024-01-02
 */

#pragma once
#include "../image/Image.h"

/**
 * @brief 画像をコンバートするクラス
 */
class Converter{
private:
    /**
     * @brief 画像ファイルパス
     * 
     */
    char*       imagePath;

    /**
     * @brief 画像フォーマット
     * 
     */
    ImageFormat format;

    /**
     * @brief 画像クラス
     * 
     */
    IImage*     image;

public:
    /**
     * @brief Construct a new Converter object
     * 
     * @param[in] imagePath 画像ファイルパス
     * @param[in] format 画像フォーマット
     */
    Converter(char* imagePath, ImageFormat format);

    /**
     * @brief Destroy the Converter object
     * 
     */
    ~Converter();

    /**
     * @brief 画像ファイルパスをプリントする
     * 
     */
    void    printImageFilePath();
};

