#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "./Manager/resource_manager.h"
#include "./Characters/player.h"
#include "./Tools/config.h"
#include "Vector2.h"
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class PlayerRoad {
public:
    PlayerRoad();

    void render(int color);
    

    ///横線
    Vector2 Line1P1;
    Vector2 Line1P2;
    Vector2 Line2P1;
    Vector2 Line2P2;
    Vector2 Line3P1;
    Vector2 Line3P2;
    Vector2 Line4P1;
    Vector2 Line4P2;
    ///縦線
    Vector2 Line5P1;
    Vector2 Line5P2;
    Vector2 Line6P1;
    Vector2 Line6P2;
    Vector2 Line7P1;
    Vector2 Line7P2;
    Vector2 Line8P1;
    Vector2 Line8P2;

    ///矢印(左)
    Vector2 ArrowLeftPoint1;
    Vector2 ArrowLeftPoint2;
    Vector2 ArrowLeftPoint3;
    Vector2 ArrowLeftPoint4;
    Vector2 ArrowLeftPoint5;
    Vector2 ArrowLeftPoint6;

    ///矢印(右)
    Vector2 ArrowLeftPoint7;
    Vector2 ArrowLeftPoint8;
    Vector2 ArrowLeftPoint9;
    Vector2 ArrowLeftPoint10;
    Vector2 ArrowLeftPoint11;
    Vector2 ArrowLeftPoint12;
};

class Background {
public:

    Background();
    ~Background();

    //背景の初期化処理
    void Init();
    //背景の更新処理
    void Update(Player* player,Map* map,char keys[256]);
    //背景の描画処理
    void Render();

private:

    ResourceManager resourceManager;

    const float totalWidth = WINDOW_WIDTH * 6;
    const float screenWidth = WINDOW_WIDTH / 2;

    float playerScreenX;
    float scrollX;
    int offsetX;
    int startIdx;

    PlayerRoad * playerRoad;
};


#endif

