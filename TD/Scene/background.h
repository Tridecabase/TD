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
    
    float getPlayerScreenX() {
        return scrollX;
    };


private:

    ResourceManager resourceManager;

    const float totalWidth = WINDOW_WIDTH * 6;
    const float screenWidth = WINDOW_WIDTH / 2;

    float playerScreenX;
    float scrollX;
    int offsetX;
    int startIdx;

};

#endif

