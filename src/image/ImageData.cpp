/**
 * @file ImageData.cpp
 * @author Yusuke Ota
 * @brief 画像データクラスの実装部
 * @version 0.3
 * @date 2024-04-15
 */

#include "Image.h"

ImageData::ImageData(){
	this->bitCount = 0;
	this->width = 0;
	this->height = 0;
	this->isPalette = false;
	this->paletteLength = 0;
	this->paletteData = NULL;
	this->palettePixelData = NULL;
	this->rgbPixelData = NULL;
	this->pixelDataLength = 0;
}
