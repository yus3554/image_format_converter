/**
 * @file Image.h
 * @author Yusuke Ota
 * @brief 画像に関わるクラス・構造体・列挙型の宣言部
 * @version 0.1
 * @date 2024-01-02
 */

#pragma once
#include <stdio.h>

/**
 * @brief 画像フォーマット列挙型
 * 
 */
enum class ImageFormat{
    BMP, PNG, OTHERS
};

/**
 * @brief 画像クラスのインターフェース
 * 
 */
struct IImage{
    /**
     * @brief Destroy the IImage object
     * 
     */
    virtual ~IImage(){}

    /**
     * @brief ファイル名をプリントする
     * 
     */
    virtual void    printFileName() = 0;
};

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
    IImage*     createImage(char* filePath);
};

/**
 * @brief 画像基底クラス
 * 
 */
class ImageBase : public IImage{
protected:
    /**
     * @brief 画像ファイルパス
     * 
     */
    const char*     filePath;

    /**
     * @brief 画像フォーマット
     * 
     */
    ImageFormat     format;

    /**
     * @brief 画像ファイルパスがNULLかどうかをチェック
     * 
     */
    void    filePathNullCheck();

public:
    /**
     * @brief Construct a new Image Base object
     * 
     */
    ImageBase();

    /**
     * @brief Construct a new Image Base object
     * 
     * @param filePath 画像ファイルパス
     */
    ImageBase(const char filePath[]);

    /**
     * @brief ファイル名をプリントする
     * 
     */
    void        printFileName();
};

/**
 * @brief BMPクラス
 * 
 */
class BMP : public ImageBase{
private:
public:
    /**
     * @brief Construct a new BMP object
     * 
     */
    BMP();

    /**
     * @brief Construct a new BMP object
     * 
     * @param filePath 画像ファイルパス
     */
    BMP(const char filePath[]);

    /**
     * @brief BMPのファイルシグネチャ
     * 
     */
    static const unsigned char  fileSignature[2];
};

/**
 * @brief PNGクラス
 * 
 */
class PNG : public ImageBase{
private:
public:
    /**
     * @brief Construct a new PNG object
     * 
     */
    PNG();

    /**
     * @brief Construct a new PNG object
     * 
     * @param filePath 画像ファイルパス
     */
    PNG(const char filePath[]);

    /**
     * @brief PNGのファイルシグネチャ
     * 
     */
    static const unsigned char  fileSignature[8];
};
