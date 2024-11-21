#pragma once
#include <Novice.h>
#include <Vector2.h>
#include "./Tools/config.h"
#include "./Entities/obj.h"
#include "drawPolygon.h"

class Title{
public:
	Title();
	///メンバー関数

    //タイトルの初期化処理
    void Init();
    //タイトルの更新処理
    void Update();
    //ステージチェンジャー
    void StageChanger();
    //タイトルの描画処理
    void Render();

	///メンバー変数
    Vector2 Window1;
    int w1Width;
    int w1Height;
    Vector2 Window2;
    int w2Width;
    int w2Height;
    Vector2 Window3;
    int w3Width;
    int w3Height;


};

