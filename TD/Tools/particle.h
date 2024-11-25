#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <vector>
#include <cstdlib>
#include <cmath>
#include "Novice.h"

struct Particle {
    float x, y;         //位置
    float vx, vy;       //速度
    float angle;        //回転角度
    unsigned int color; //色
    int life;       //命
};

class ParticleGenerator {
public:
    ParticleGenerator() {}

    void GenerateParticles(float x, float y) {
        if (maxlife <= 0) {
            return;
        }

        for (int i = 0; i < particlesPerFrame; ++i) {
            Particle p;
            p.x = x;
            p.y = y;

            float speed = static_cast<float>(rand()) / RAND_MAX * maxSpeed;
            float direction = static_cast<float>(rand()) / RAND_MAX * 360.0f;
            p.vx = speed * cos(direction * static_cast<float>(M_PI) / 180.0f);
            p.vy = speed * sin(direction * static_cast<float>(M_PI) / 180.0f);

            p.angle = static_cast<float>(rand()) / RAND_MAX * 360.0f;
            p.color = 0x4BBC5444;
            p.life = rand() % maxlife + 1;


            if (p.life <= 0) {
                continue;
            }

            particles.push_back(p);
        }
    }


    void Destroy(float x, float y) {
        for (int i = 0; i < 20; ++i) {
            Particle p;
            p.x = x;
            p.y = y;
            float speed = static_cast<float>(rand()) / RAND_MAX * maxSpeed;
            float direction = static_cast<float>(rand()) / RAND_MAX * 360.0f;
            p.vx = 2 * speed * cos(direction * static_cast<float>(M_PI) / 180.0f);
            p.vy = 2 * speed * sin(direction * static_cast<float>(M_PI) / 180.0f);
            p.angle = static_cast<float>(rand()) / RAND_MAX * 360.0f;
            p.color = 0xFF000044;
            p.life = rand() % maxlife + 30;
            particles.push_back(p);
        }
    }

    void Render() {
        for (auto it = particles.begin(); it != particles.end();) {
            Novice::DrawBox(
                static_cast<int>(it->x), static_cast<int>(it->y),
                10, 10, 
                it->angle,
                it->color,
                kFillModeSolid 
            );

            it->x += it->vx;
            it->y += it->vy;
            --(it->life);

            if (it->life <= 0) {
                it = particles.erase(it); //削除
            }
            else {
                ++it;
            }
        }
    }

private:
    std::vector<Particle> particles; //粒子リスト
    const int particlesPerFrame = 1; //生成数/フレーム
    const int maxlife = 60;      //最大フレーム
    const float maxSpeed = 3.0f;     //最大速度
};

#endif