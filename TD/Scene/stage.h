#ifndef STAGE_H
#define STAGE_H

#include "./Manager/resource_manager.h"
#include "./Characters/player.h"
#include "./Characters/enemy.h"
#include "./Scene/background.h"
#include "./Entities/map.h"
#include "UI.h"
#include "./Entities/bullet.h"
#include "./Entities/enemy_bullet.h"
#include "./Tools/config.h"
#include "effect.h"
#include "Vector2.h"
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

    //ステージチェンジャー
    bool StageChanger(char key[256], char preKey[256]);

    //プレイヤーの宣言
    Player* player;
    //敵の宣言
    Enemy* enemy;

private:

    ResourceManager resourceManager;


    ///開幕clock
    int openClock;
    int openTime;

    ///ループアニメーションclock
    int aniClock;
    int aniTime;

    ///終了clock
    int scClock;
    int scTime;
    int scFlat;


    //背景の宣言
    Background* background;
    //プレイヤーマップの宣言
    Map* map;
    //プレイヤ弾丸の宣言
    Bullet* bullet;
    BulletA* bulletA;
    BulletB* bulletB;
    BulletC* bulletC;
    BulletD* bulletD;
    //敵弾丸の宣言
    FunnelBullet* funnelBullet;
    //UIの宣言
    UI* ui;
};

#endif
