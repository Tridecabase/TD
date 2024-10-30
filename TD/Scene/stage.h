#ifndef STAGE_H
#define STAGE_H

#include "./Characters/player.h"
#include "./Scene/background.h"
#include "./Manager/resource_manager.h"
#include "Vector2.h"
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Stage {
public:

    Stage();
    ~Stage();

    //マップの初期化処理
    void Init();
    //ステージの更新処理
    void Update();
    //ステージの描画処理
    void Render();

private:

    ResourceManager resourceManager;

    //背景の宣言
    Background* background;
};

#endif
