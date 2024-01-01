/**
 * 画像ヘッダーファイル
*/
#pragma once
#include <stdio.h>

/**
 * 画像フォーマット列挙型
*/
enum class ImageFormat{
    BMP, PNG, OTHERS
};

/**
 * 画像インターフェース
*/
struct IImage{
    virtual ~IImage(){}
    virtual void    printFileName() = 0;
};

/**
 * 画像ファクトリークラス
*/
class ImageFactory{
private:
    ImageFormat judgeImageFormat(char*);
    bool        isCorrectFileSignature(int, unsigned char*, int, const unsigned char*);
public:
    IImage*     createImage(char*);
};

/**
 * 画像基底クラス
*/
class ImageBase : public IImage{
protected:
    const char*     filePath;
    ImageFormat     format;
    FILE*   file;
    void    filePathNullCheck();
public:
    ImageBase();
    ImageBase(const char[]);
    void        printFileName();
};

/**
 * BMPクラス
*/
class BMP : public ImageBase{
private:
public:
    BMP();
    BMP(const char[]);
    static const unsigned char  fileSignature[2];
};

/**
 * PNGクラス
*/
class PNG : public ImageBase{
private:
public:
    PNG();
    PNG(const char[]);
    static const unsigned char  fileSignature[8];
};
