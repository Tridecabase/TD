#ifndef CIRCLE_EFFECT_H
#define CIRCLE_EFFECT_H

#include "Novice.h"
#include <cstdlib>
#include <ctime>
#include <vector>

//2Dベクトル構造体
struct Vector2 {
    float x, y;
};

class CircleEffect {
public:
    //コンストラクタ
    CircleEffect() {
        frameTimer = 0;  // フレームタイマーを初期化
        srand(static_cast<unsigned int>(time(0)));  // ランダム数生成のためのシードを初期化
    }

    // デストラクタ
    ~CircleEffect() {
        //現時点では特別なクリーンアップは必要なし
    }

    //サークル効果の更新
    void Update(Vector2 pos) {
        // フレームカウントを増加させる
        frameTimer++;

        // 5〜10フレームごとに新しい円を生成
        if (frameTimer >= rand() % 6 + 5) {  //ランダムに5〜10フレーム
            frameTimer = 0;  // フレームカウントをリセット
            Circle newCircle = { pos, 1500.0f, 0, true };  //新しい円を初期化
            circles.push_back(newCircle);  //円をリストに追加
        }

        // すべての円を更新
        for (auto& circle : circles) {
            if (circle.isActive) {
                // 円の半径を減少させ、消失させる
                circle.radius -= 1.0f;
                if (circle.radius <= 0) {
                    circle.isActive = false;  //半径が0以下になったら円を非アクティブに
                }
            }
        }
    }

    // すべてのアクティブな円を描画
    void Draw() {
        for (auto& circle : circles) {
            if (circle.isActive) {
                Novice::DrawEllipse(
                    static_cast<int>(circle.pos.x),
                    static_cast<int>(circle.pos.y),
                    static_cast<int>(circle.radius),
                    static_cast<int>(circle.radius),
                    0.0f,
                    0xFFFFFF00, 
                    kFillModeWireFrame
                );
            }
        }
    }

private:
    // 円のデータ構造体
    struct Circle {
        Vector2 pos;      //位置
        float radius;     //半径
        int frameCount;   //現在のフレーム数
        bool isActive;    //アクティブかどうか
    };

    std::vector<Circle> circles;  //アクティブな円を保持するリスト
    int frameTimer;               //新しい円を生成するためのフレームタイマー
};

#endif