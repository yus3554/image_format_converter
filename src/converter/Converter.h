/**
 * コンバーターヘッダーファイル
*/
#pragma once
#include "../image/Image.h"

class Converter{
private:
    char*       imagePath;
    ImageFormat format;
    IImage*     image;
public:
    Converter(char*, ImageFormat);
    ~Converter();
    void    printImageFilePath();
};

