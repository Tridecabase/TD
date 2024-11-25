#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <cstdlib>
#include <cmath>
#include "Novice.h"

//最大Particle数
#define MAX_PARTICLES 1000

struct Particle {
    float x, y;         //位置
    float vx, vy;       //速度
    float angle;        //回転角度
    unsigned int color; //色
    int life;           //生命
    bool active;        //活動状態
};

class ParticleGenerator {
public:
    ParticleGenerator() : nextParticleIndex(0) {
        //すべてのParticleを非活動状態に初期化
        for (int i = 0; i < MAX_PARTICLES; ++i) {
            particles[i].active = false;
        }
    }

    void GenerateParticles(float x, float y, unsigned int color) {

        Particle& p = particles[nextParticleIndex];
        if (!p.active) {
            p.x = x;
            p.y = y;

            float speed = static_cast<float>(rand()) / RAND_MAX * maxSpeed;
            float direction = static_cast<float>(rand()) / RAND_MAX * 360.0f;
            p.vx = speed * cos(direction * static_cast<float>(M_PI) / 180.0f);
            p.vy = speed * sin(direction * static_cast<float>(M_PI) / 180.0f);

            p.angle = static_cast<float>(rand()) / RAND_MAX * 360.0f;
            p.color = color;
            p.life = rand() % maxlife + 1;
            p.active = true;
        }

        // 次の粒子のインデックスを更新
        nextParticleIndex = (nextParticleIndex + 1) % MAX_PARTICLES;
    }

    // 破壊時に赤い粒子を生成する
    void Destroy(float x, float y, unsigned int color) {
        for (int i = 0; i < 20; ++i) {
            GenerateParticles(x, y, color);
        }
    }

    void Render() {
        for (int i = 0; i < MAX_PARTICLES; ++i) {
            Particle& p = particles[i];
            if (p.active) {
                Novice::DrawBox(
                    static_cast<int>(p.x), static_cast<int>(p.y),
                    10, 10,
                    p.angle,
                    p.color,
                    kFillModeSolid
                );

                p.x += p.vx;
                p.y += p.vy;
                --(p.life);

                //生命値が0になったら非活動状態にする
                if (p.life <= 0) {
                    p.active = false;
                }
            }
        }
    }

private:
    Particle particles[MAX_PARTICLES]; //固定サイズのParticle配列
    int nextParticleIndex;             //次に使用するParticleのインデックス
    const int maxlife = 60;            //最大生命値
    const float maxSpeed = 3.0f;       //最大速度
};

#endif