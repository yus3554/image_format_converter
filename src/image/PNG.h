/**
 * @file PNG.h
 * @author Yusuke Ota
 * @brief PNGに関わるクラス・構造体・列挙型の宣言部
 * @version 0.3
 * @date 2024-04-15
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"
#include "../utils/Utils.h"

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
