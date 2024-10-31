#include "wave_generator.h"
#include "./Tools/config.h"

/*
 * WaveGenerator クラスの機能概要
 *
 * このクラスは、異なる種類の波形を生成および描画するための機能を提供します。
 * 正弦波、ランダム波、ノイズ波の三種類の波を作成することができます。
 * 各波形は指定されたパラメータに基づいてリアルタイムで更新され、描画されます。
 *
 * 【コンストラクタの説明】
 * - startY: Y座標
 * - numbers: 線の数
 * - amp: 振幅
 * - wave_length: 波長
 * - speed: 速度
 * - mod_length: 変調の波長
 * - color: 色
 *
 * 【メソッドの詳細】
 * - WaveUpdate: 正弦波の生成
 * - WaveRandomUpdate: 振幅が変動するランダム波の生成
 * - WaveNoiseUpdate: ランダムな振幅と位相を持つノイズ波の生成
 * - Render: 波の描画
 *
 * 【使用方法】
 * WaveGenerator クラスをインスタンス化し、パラメータを設定して、
 * WaveUpdate、WaveRandomUpdate、または WaveNoiseUpdate を呼び出します。
 * 最後に、Render を呼び出して、計算された波を画面に描画します。
 *
 * 例:
 * WaveGenerator* wave1;
 * wave1 = new WaveGenerator(100.0f, 200, 50, 100, 2.0f, 50, WHITE);
 * wave1->WaveUpdate();
 * wave1->Render();
 */

 ////////////////////////////////////////////////////////////////////////////////////////////
 //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
 ////////////////////////////////////////////////////////////////////////////////////////////
WaveGenerator::WaveGenerator(float startY, int numbers, int amp, int wave_length, float speed, int mod_length, unsigned int color)
    : startX(0.0f), startY(startY), total_length(WINDOW_WIDTH), numbers(numbers),
    amp(amp), wave_length(wave_length), speed(speed),
   mod_length(mod_length), offset(0.0f), color(color) {

    //波の座標を格納する動的配列を作成
    x1 = new float[numbers];
    y1 = new float[numbers];
    x2 = new float[numbers];
    y2 = new float[numbers];
}
WaveGenerator::~WaveGenerator() {
    delete[] x1;
    delete[] y1;
    delete[] x2;
    delete[] y2;
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
/*
 * WaveUpdate メソッド
 *
 * 正弦波の座標を更新します。波が進行するにつれて、各点のY座標を計算します
 */
void WaveGenerator::WaveUpdate() {
    //波がスクリーンを超えた場合、巻き戻す
    offset += speed;
    if (offset >= wave_length) {
        offset -= wave_length;
    }

    //各点の座標計算
    for (int i = 0; i < numbers; ++i) {
        x1[i] = startX + i * (total_length / numbers);
        y1[i] = startY + static_cast<float>(amp * sin(2 * M_PI * (i / static_cast<float>(wave_length) + offset / wave_length)));
        x2[i] = startX + (i + 1) * (total_length / numbers);
        y2[i] = startY + static_cast<float>(amp * sin(2 * M_PI * ((i + 1) / static_cast<float>(wave_length) + offset / wave_length)));
    }
}


/*
 * WaveRandomUpdate メソッド
 *
 * ランダムな振幅の波を生成し、座標を更新します
 */
void WaveGenerator::WaveRandomUpdate() {
    //波がスクリーンを超えた場合、巻き戻す
    offset += speed;
    if (offset >= wave_length) {
        offset -= wave_length;
    }

    //各点の座標計算
    for (int i = 0; i < numbers; ++i) {
        //振幅変調を計算
        float mod_amp = static_cast<float>(1.0f + 0.5f * sin(2 * M_PI * (static_cast<double>(i) /mod_length)));
        //現在の振幅を計算
        float current_amp = amp * mod_amp;

        x1[i] = startX + i * (total_length / numbers);
        y1[i] = startY + static_cast<float>(current_amp * sin(2 * M_PI * (i / static_cast<float>(wave_length) + offset / wave_length)));
        x2[i] = startX + (i + 1) * (total_length / numbers);
        y2[i] = startY + static_cast<float>(current_amp * sin(2 * M_PI * ((i + 1) / static_cast<float>(wave_length) + offset / wave_length)));
    }
}

/*
 * WaveNoiseUpdate メソッド
 *
 * ノイズ波を生成し、座標を更新します
 */
void WaveGenerator::WaveNoiseUpdate() {
    //波がスクリーンを超えた場合、巻き戻す
    offset += speed;
    if (offset >= wave_length) {
        offset -= wave_length;
    }

    //各点の座標計算
    for (int i = 0; i < numbers; ++i) {
        //ランダム振幅を生成
        int random_amp = amp + (rand() % 5 - 2);
        //ランダムな位相を生成
        float tmp_offset = (rand() % 10 - 5) / 50.0f;

        x1[i] = startX + i * (total_length / numbers);
        y1[i] = startY + static_cast<float>(random_amp * sin(2 * M_PI * (i / static_cast<float>(wave_length) + offset / wave_length + tmp_offset)));
        x2[i] = startX + (i + 1) * (total_length / numbers);
        y2[i] = startY + static_cast<float>(random_amp * sin(2 * M_PI * ((i + 1) / static_cast<float>(wave_length) + offset / wave_length + tmp_offset)));
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
//波の描画
void WaveGenerator::Render() const {

    for (int i = 0; i < numbers - 1; ++i) {
        Novice::DrawLine(
            static_cast<int>(x1[i]), 
            static_cast<int>(y1[i]), 
            static_cast<int>(x2[i]), 
            static_cast<int>(y2[i]), 
            color);
    }

}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////