/**
 * @file Converter.h
 * @author Yusuke Ota
 * @brief 画像フォーマットを変換するクラスの宣言部
 * @version 0.1
 * @date 2024-01-02
 */

#pragma once
#include "../image/Image.h"
#include "../image/ImageFactory.h"

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
     * @brief 変換したい画像フォーマット
     * 
     */
    ImageFormat convertFormat;

    /**
     * @brief 画像クラス
     * 
     */
    IImage*     image;

    /**
     * @brief 画像クラスのファクトリー
     * 
     */
    ImageFactory* factory;

public:
    /**
     * @brief Construct a new Converter object
     * 
     * @param[in] imagePath 画像ファイルパス
     * @param[in] convertFormat 変換したい画像フォーマット
     */
    Converter(char* imagePath, ImageFormat convertFormat);

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

    /**
     * @brief 変換を実行する
     * 
     */
    void    executeConvert();
};

