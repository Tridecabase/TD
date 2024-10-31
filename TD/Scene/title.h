#ifndef TITLE_H
#define TITLE_H

#include "./Manager/resource_manager.h"
#include "./Tools/config.h"
#include "Vector2.h"
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Title {
public:

    Title();
    ~Title();

    //背景の初期化処理
    void Init();
    //背景の更新処理
    void Update();
    //背景の描画処理
    void Render();

private:

    ResourceManager resourceManager;

    float radius;

    float angel_alpha;
    float angel_beta;

    float vel;

    float line_alpha;
    float line_beta;
    float quad_width;
    float quad_height;

    int textureHandle;

};

#endif
