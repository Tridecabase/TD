#ifndef PARTICLE_H
#define PARTICLE_H

#define _USE_MATH_DEFINES
#include <novice.h>
#include <cstdlib>
#include <cmath>
#include "./Tools/config.h"

//パーティクル構造体
struct Particle {
    float x, y;         //位置
    float vx, vy;       //速度
    float life;         //命
    float angle;        //回転角度
    unsigned int color; //色
};

class ParticleGenerator {
public:
    ParticleGenerator() : particleCount(0) {}

    //ランダムな方向にパーティクルを生成する関数
    void GenerateParticles(float x, float y) {
        for (int i = 0; i < 10; ++i) {
            if (particleCount >= MAX_PARTICLES) break;

            float angle = randomFloat(0.0f, 360.0f);
            float speed = randomFloat(1.0f, 3.0f);
            particles[particleCount++] = {
                x, y,
                cosf(angle * static_cast<float>(M_PI) / 180.0f) * speed,
                sinf(angle * static_cast<float>(M_PI) / 180.0f) * speed,
                randomFloat(0.2f, 0.6f),
                0.0f,
                0xAAAAAAFF
            };
        }

        //パーティクルの更新
        updateParticles();
    }

    //指定した方向パーティクルを生成する関数
    void GenerateDirectParticle(float x, float y, float angle) {
        if (particleCount >= MAX_PARTICLES) return;

        float speed = randomFloat(2.0f, 5.0f);
        particles[particleCount++] = {
            x, y,
            cosf(angle * static_cast<float>(M_PI) / 180.0f) * speed,
            sinf(angle * static_cast<float>(M_PI) / 180.0f) * speed,
            randomFloat(0.3f, 1.0f),
            angle,
            0xAAAAAAFF
        };

        //パーティクルの更新
        updateParticles();
    }

    //パーティクルを描画する関数
    void Render() const {
        for (int i = 0; i < particleCount; ++i) {
            const Particle& p = particles[i];
            Novice::DrawBox(
                static_cast<int>(p.x), static_cast<int>(p.y),    //位置
                10, 10,      //幅と高さ
                p.angle,     //回転角度
                p.color,     //色
                kFillModeSolid
            );
        }
    }

private:
    //固定サイズのパーティクル配列
    Particle particles[MAX_PARTICLES];
    //現在のパーティクル数
    int particleCount;

    //パーティクルの更新
    void updateParticles() {
        for (int i = 0; i < particleCount; ++i) {
            Particle& p = particles[i];
            p.x += p.vx; 
            p.y += p.vy;
            p.life -= 0.024f;

            if (p.life <= 0.0f) {
                //配列の最後のパーティクルで上書き
                particles[i] = particles[--particleCount]; 
                --i;
            }
        }
    }

    //浮動小数点数を生成する関数
    static float randomFloat(float min, float max) {
        return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
    }
};

#endif // PARTICLE_GENERATOR_H
