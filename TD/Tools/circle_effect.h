﻿#ifndef CIRCLE_EFFECT_H
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
        frameTimer = 0;
        srand(static_cast<unsigned int>(time(0)));
    }

    // デストラクタ
    ~CircleEffect() {
    }

    //サークル効果の更新
    void Update(Vector2 pos) {
        frameTimer++;

        if (frameTimer >= rand() % 6 + 5) {
            frameTimer = 0; 
            Circle newCircle = { pos, 1500.0f, 0, true };
            circles.push_back(newCircle);
        }

        for (auto& circle : circles) {
            if (circle.isActive) {
                //円の半径を減少させ、消失させる
                circle.radius -= 1.0f;
                if (circle.radius <= 0) {
                    circle.isActive = false;
                }
            }
        }
    }

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
    //構造体
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