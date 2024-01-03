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
 * @brief 画像データ
 * 
 */
class ImageData{
public:
    // TODO: いろんな画像に関するデータを入れる
    // 
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
    virtual void        printFileName() = 0;

    /**
     * @brief Get the Image Data object
     * 
     * @return ImageData 
     */
    virtual ImageData   getImageData()  = 0;

    /**
     * @brief 画像を生成する
     * 
     */
    // TODO: 画像を生成する。なので、ConverterクラスでもこのIImageクラスをインスタンス化し、この関数を実行して画像を生成する
    virtual void        generateImage(ImageData data)   = 0;
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

    ImageData   getImageData();
    void        generateImage(ImageData data);
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
     * @param filePath 画像ファイルパス
     */
    BMP(const char filePath[]);

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
     * @param filePath 画像ファイルパス
     */
    PNG(const char filePath[]);

    /**
     * @brief PNGのファイルシグネチャ
     * 
     */
    static const unsigned char  fileSignature[8];

    /**
     * @brief PNGの拡張子名
     * 
     */
    static const char           extension[4];
};
