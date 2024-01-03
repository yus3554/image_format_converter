/**
 * @file ImageFactory.h
 * @author Yusuke Ota
 * @brief 画像クラスのファクトリークラスの宣言部
 * @version 0.1
 * @date 2024-01-04

 */

#pragma once
#include <stdio.h>
#include "Image.h"

/**
 * @brief 画像クラスのファクトリークラス
 * 
 */
class ImageFactory{
private:
    /**
     * @brief  指定された画像ファイルがどの画像フォーマットかを判定する
     * 
     * @param filePath 画像ファイルパス
     * @return ImageFormat 判定した画像フォーマット
     */
    ImageFormat judgeImageFormat(char* filePath);

    /**
     * @brief ファイルシグネチャが正しいかどうかを判定する
     * 
     * @param srcSigSize 判定元のファイルシグネチャ長
     * @param srcSig 判定元のファイルシグネチャ
     * @param destSigSize 判定先のファイルシグネチャ長
     * @param destSig 判定先のファイルシグネチャ
     * @return true 判定元と判定先が等しい
     * @return false 判定元と判定先が等しくない
     */
    bool        isCorrectFileSignature(
        int srcSigSize, unsigned char* srcSig, int destSigSize, const unsigned char* destSig
    );
 
public:
    /**
     * @brief 画像ファイルに適したクラスの画像クラスを作成する
     * 
     * @param filePath 画像ファイルパス
     * @return IImage* 画像ファイルに適した画像クラスのインターフェース
     */
    IImage*     createImageFromPath(char* filePath);

    /**
     * @brief 画像フォーマットに適したクラスの画像クラスを作成する
     * 
     * @param format 画像フォーマット
     * @param filePath 画像ファイルパス
     * @return IImage* 画像フォーマットに適した画像クラスのインターフェース
     */
    IImage*     createImageFromFormat(ImageFormat format, char* filePath = NULL);
};
