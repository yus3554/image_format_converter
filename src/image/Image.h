/**
 * 画像ヘッダーファイル
*/
#include <stdio.h>

/**
 * 画像インターフェース
*/
struct IImage{
    virtual void    open(const char filePath[]) = 0;
    virtual void    create() = 0;
    virtual void    save(const char saveFilePath[]) = 0;
    virtual void    printFileName() = 0;
};

/**
 * 画像基底クラス
*/
class ImageBase : public IImage{
private:
    const char*   filePath;
    int     fileSize;
    FILE*   file;
    bool    isCorrectFile;
    void    calcFileSize();
    void    judgeCollectFile();
public:
    ImageBase();
    ImageBase(const char filePath[]);
    void    open(const char filePath[]);
    void    create();
    void    save(const char saveFilePath[]);
    void    printFileName();
};

/**
 * TGAクラス
*/
class TGA : public ImageBase{
private:
public:
    TGA();
};

