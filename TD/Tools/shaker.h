#ifndef SHAKER_H
#define SHAKER_H

#include <stdlib.h>
#include <math.h>
#include "config.h"

class Shaker {
public:

    //被撃時の振動
    static void ShakeOnHit(float& posX, float& posY, float intensity) {
        static float tempX = posX;
        static float tempY = posY;

        posX = float (tempX + ((rand() % 200 - 100) / 100.0f) * intensity);
        posY = float (tempY + ((rand() % 200 - 100) / 100.0f) * intensity);
    }

    //クリティカルヒット時の振動
    static void CriticalShake(float& posX, float& posY, float intensity) {
        static float tempX = posX;
        static float tempY = posY;

        posX = float(tempX + ((rand() % 50 - 25) / 25.0f) * intensity);
        posY = float(tempY + ((rand() % 50 - 25) / 25.0f) * intensity);
    }

    //スクリーン揺れの遅い振動
    static void SlowShake(float& posX, float& posY, float intensity) {
        static float tempX = posX;
        static float tempY = posY;

        posX = float (tempX + sin(rand() % 10) * intensity);
        posY = float (tempY + cos(rand() % 10) * intensity);
    }

    //スクリーン揺れの速い振動
    static void QuickShake(float& posX, float& posY, float intensity) {
        static float tempX = posX;
        static float tempY = posY;

        posX = float (tempX + ((rand() % 10 - 5) / 10.0f) * intensity);
        posY = float (tempY + ((rand() % 10 - 5) / 10.0f) * intensity);
    }

    static void EnemyDiving(float& enemyPosX, float& enemyPosY, float playerPosX, float playerPosY) {
        static bool isReturning = false;
        static float duration = 0.3f;
        static float elapsed_time = 0.0f;

        elapsed_time += DELTA_TIME;

        if (!isReturning) {
            float factor = (elapsed_time * elapsed_time) / (duration * duration);
            enemyPosX = enemyPosX + (playerPosX - enemyPosX) * factor;
            enemyPosY = enemyPosY + (playerPosY - enemyPosY) * factor;


            if (elapsed_time >= duration) {
                isReturning = true;
                elapsed_time = 0.0f;
            }
        }
        else {

            float factor = (elapsed_time * elapsed_time) / (duration * duration);
            enemyPosX = playerPosX + (enemyPosX - playerPosX) * factor;
            enemyPosY = playerPosY + (enemyPosY - playerPosY) * factor;

            if (elapsed_time >= duration) {
                isReturning = false;
                elapsed_time = 0.0f;
            }
        }
    }
};

#endif

