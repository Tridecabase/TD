#pragma once
#include <Novice.h>
#include <Vector2.h>
#include <math.h>
#include "./Entities/obj.h"
#include "./Tools/config.h"


class RuningBinary {
public:

	RuningBinary();
	~RuningBinary();

	void Init(const float posX, const float posY, const int showWidth, const int showHeight, const int wordWidth);
	void Updata();
	void Render();

	//句
	WordFloat* wordFloat[20];
	///整体のpos
	Vector2 pos_;
	///表示範囲
	int width_;
	int height_;
	///落ち速度
	int clock_;
	int time_;


};

/// <summary>
/// スクリーンチェンジ関数、物書く系
/// </summary>
/// <param name="clock">時間</param>
/// <param name="time">最大時間</param>
/// <param name="color">色</param>
/// <param name="type">0:なんもないからスクリーンまで, 1 = スクリーンからなんもないまで</param>
void stageChangeShow(const int clock,const int time, const int color, int type);