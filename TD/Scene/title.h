#pragma once
#include <Novice.h>
#include <Vector2.h>
#include <time.h>
#include "./Tools/config.h"
#include "./Entities/obj.h"
#include "drawPolygon.h"

class Title {
public:
	Title();
	~Title();
	///メンバー関数

	//タイトルの初期化処理
	void Init();

	
	void DrawTitle(const int posX, const int posY, const int width, int color);
	void DrawGameStart(const int posX, const int posY, const int width, int color);

	//タイトルの更新処理
	void Update();
	//ステージチェンジャー
	void StageChanger();
	//タイトルの描画処理
	void Render();

	///メンバー変数
	int randNumber;

	Obj* window[4];
	int openClock;
	int openTime;

	int yMoveNum[6];
	int changeNum[6];
	int changeClockClock[6];
	int changeClockTime[6];

};

