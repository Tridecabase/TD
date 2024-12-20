﻿#pragma once
#include <Novice.h>
#include <Vector2.h>
#include <time.h>
#include "./Tools/config.h"
#include "./Entities/obj.h"
#include "./Characters/player.h"
#include "drawPolygon.h"
#include "effect.h"
#include "UI.h"

class StageClear {
public:
	StageClear();
	~StageClear();
	///メンバー関数

	//タイトルの初期化処理
	void Init();


	void DrawClear(const int posX, const int posY, const int width, int color);
	void DrawCongratulations(const int posX, const int posY, const int width, int color);
	void DrawBack(const int posX, const int posY, const int width, int color);

	//タイトルの更新処理
	void Update();
	//ステージチェンジャー
	bool StageChanger();
	//タイトルの描画処理
	void Render();

	///メンバー変数
	int randNumber;

	UI* ui;

	Obj* window[4];
	int openClock;
	int openTime;

	int aniClock;
	int aniTime;

	int scClock;
	int scTime;
	bool scFlat;

	int yMoveNum[6];
	int changeNum[6];
	int changeClockClock[6];
	int changeClockTime[6];

	RuningBinary* runingBinary;

	Player* player;
};

