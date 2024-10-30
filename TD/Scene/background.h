#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "./Manager/resource_manager.h"
#include "./Tools/config.h"
#include "Vector2.h"
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Background {
public:

    Background();
    ~Background();

    //背景の初期化処理
    void Init();
    //背景の更新処理
    void Update();
    //背景の描画処理
    void Render();

private:

    ResourceManager resourceManager;
};

#endif

