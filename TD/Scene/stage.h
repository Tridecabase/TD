#ifndef STAGE_H
#define STAGE_H

#include "./Manager/resource_manager.h"
#include "./Characters/player.h"
#include "./Characters/enemy.h"
#include "./Scene/background.h"
#include "./Entities/map.h"
#include "UI.h"
#include "./Entities/bullet.h"
#include "./Tools/config.h"
#include "Vector2.h"
#include "UI.h"
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

///////////////////////////

class Stage {
public:

    Stage();
    ~Stage();

    //マップの初期化処理
    void Init();
    //ステージの更新処理
    void Update(char keys[256], char preKeys[256]);
    //ステージの描画処理
    void Render();

    //プレイヤーの宣言
    Player* player;
    //敵の宣言
    Enemy* enemy;

private:

    ResourceManager resourceManager;

    //背景の宣言
    Background* background;
    //プレイヤーマップの宣言
    Map* map;
    //プレイヤ弾丸の宣言
    BulletA* bulletA;
    BulletB* bulletB;
    //UIの宣言
    UI* ui;
};

#endif
