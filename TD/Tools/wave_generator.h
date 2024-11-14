#ifndef WAVE_GENERATOR_H
#define WAVE_GENERATOR_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <novice.h>
#include "./Tools/config.h"

class WaveGenerator {
public:

    /*コンストラクタ
    *startY: 開始Y座標
    *numbers: 線の数
    *amp: 振幅
    *wave_length: 波長
    *speed: 速度
    *modLength: モジュレーション波長
    *color: 色
    */
	WaveGenerator(float startX, float startY, int total_length ,int numbers, int amp, int wave_length, float speed, int mod_length, unsigned int color);
    //デストラクタ
    ~WaveGenerator();

    //正弦波
    void WaveUpdate();
    //ランダム波形
    void WaveRandomUpdate();
    //ノイズ波形
    void WaveNoiseUpdate();
    //波の描画
    void Render() const;

    //座標配列
    float* x1;
    float* y1;
    float* x2;
    float* y2;

    //長さ
    int total_length;
    //線の数
    int numbers;
    //色
    unsigned int color;

private:

    //開始位置
    float startX;
    float startY;
    //振幅
    int amp;
    //波長
    int wave_length;
    //速度
    float speed;
    //モジュレーション波長
    int mod_length;
    //位相
    float offset;

    WaveGenerator(const WaveGenerator&) = delete;
    WaveGenerator& operator=(const WaveGenerator&) = delete;
};

#endif 
