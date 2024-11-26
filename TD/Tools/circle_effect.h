#ifndef CIRCLE_EFFECT_H
#define CIRCLE_EFFECT_H

#include "Novice.h"
#include "Vector2.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

class CircleEffect {
public:
    //コンストラクタ
    CircleEffect() {
        frameTimer = 0;
        srand(static_cast<unsigned int>(time(0)));
    }

    //デストラクタ
    ~CircleEffect() {
    }

    //サークル効果の更新
    void Update(Vector2 pos) {
        frameTimer++;

        //新しい円を生成
        if (frameTimer >= rand() % 30 + 5) {
            frameTimer = 0;
            Circle newCircle = { pos, 2400.0f, 0, true };
            circles.push_back(newCircle);
        }

        //更新サークルの状態
        for (auto& circle : circles) {
            circle.pos = pos;

            if (circle.isActive) {
                //円の半径を減少させ、消失させる
                circle.radius -= 3.0f;
                if (circle.radius <= 0) {
                    circle.isActive = false;
                }
            }
        }
    }

    //描画
    void Draw() {
        for (auto& circle : circles) {
            if (circle.isActive) {
                //反向のtを計算
                float t = 1.0f - (circle.radius / 2400.0f);
                float alphaFactor = pow(t, 2.0f);

                //色の計算
                unsigned int color = GetColorBasedOnTime(t, alphaFactor);

                //描画
                Novice::DrawEllipse(
                    static_cast<int>(circle.pos.x),
                    static_cast<int>(circle.pos.y),
                    static_cast<int>(circle.radius),
                    static_cast<int>(circle.radius),
                    0.0f,
                    color,
                    kFillModeWireFrame
                );
            }
        }
    }

private:

    struct Circle {
        Vector2 pos;      //位置
        float radius;     //半径
        int frameCount;   //現在のフレーム数
        bool isActive;    //アクティブかどうか
    };

    std::vector<Circle> circles;  //アクティブな円を保持するリスト
    int frameTimer;               //新しい円を生成するためのフレームタイマー

    //時間に基づいて色を取得する
    unsigned int GetColorBasedOnTime(float t, float alphaFactor) {
        unsigned char r, g, b, alpha;

        if (t < 0.25f) {
            r = static_cast<unsigned char>(255);
            g = static_cast<unsigned char>(69);
            b = static_cast<unsigned char>(58);
        }
        else if (t < 0.5f) {
            r = static_cast<unsigned char>(255);
            g = static_cast<unsigned char>(165);
            b = static_cast<unsigned char>(0);
        }
        else if (t < 0.75f) {
            r = static_cast<unsigned char>(255);
            g = static_cast<unsigned char>(215);
            b = static_cast<unsigned char>(0);
        }
        else {
            r = static_cast<unsigned char>(246);
            g = static_cast<unsigned char>(140);
            b = static_cast<unsigned char>(0);
        }

        alpha = static_cast<unsigned char>(255 * alphaFactor);

        return (r << 24) | (g << 16) | (b << 8) | alpha;
    }
};

#endif