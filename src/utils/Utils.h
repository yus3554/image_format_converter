/**
 * @file Utils.h
 * @author Yusuke Ota
 * @brief ユーティリティ関数の宣言部
 * @version 0.1
 * @date 2024-01-06
 */

#include <stdio.h>
#include <math.h>

void printCharsToHex(int charLength, unsigned char* chars);

/**
 * @brief char配列を16進数としてintに変換
 * 
 * @param charLength 一括りにしたいcharの長さ
 * @param chars 
 * @param isLittleEndian
 * @return int 
 */
int charsToInt(int charLength, unsigned char* chars, bool isLittleEndian);

/**
 * @brief intをリトルエンディアンの16進数としてchar配列に変換
 * 
 * @param charLength 
 * @param num 
 * @return char* 
 */
unsigned char* intToChars(int charLength, unsigned int num);


