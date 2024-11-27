#pragma once
#include <Novice.h>
#include <Vector2.h>
#include <math.h>
#include <time.h>
#include "./Entities/obj.h"
#include "./Tools/config.h"


class RuningBinary {
public:

	RuningBinary();
	~RuningBinary();

	void Init(const float posX, const float posY, const int showWidth, const int showHeight, const int wordWidth, const int clock);
	void Updata();
	void Render(const int color);

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


#pragma region Timer
class Timer {
public:
	Timer();

	/// <summary>
	/// timeを0にする初期化
	/// </summary>
	/// <param name="time">Timerのマクス時間</param>
	void Init0(int time);

	/// <summary>
	/// timeをMixにする初期化
	/// </summary>
	/// <param name="time">Timerのマクス時間</param>
	void InitM(int time);

	/// <summary>
	/// Timerをマクスにすると止まる
	/// </summary>
	void ToMix();

	/// <summary>
	/// Timerをマクスにすると0になって、止まる。1以上になると動く
	/// </summary>
	void ToMixZero();

	/// <summary>
	/// Timerを0にすると止まる
	/// </summary>
	void ToZero();

	/// <summary>
	/// Timerを0にするとマクスになって、止まる。Mix - 1以下になると動く
	/// </summary>
	void ToZeroMix();

	/// <summary>
	/// 無休Upタイマー
	/// </summary>
	void foreverUp();

	/// <summary>
	/// 無休Downタイマー
	/// </summary>
	void foreverDown();

	/// <summary>
	/// アニメーション用の無休タイマー、1秒12フレームで int形数字を出力
	/// </summary>
	/// <returns></returns>
	void AnimationF();

	/// <summary>
	/// アニメーション用のタイマー、秒を12フレームの形で int形数字を出力
	/// </summary>
	/// <returns></returns>
	int FrameChange();



	int clock_;
	int time_;
};
#pragma endregion 

class BoxV1 {
public:
	BoxV1();
	~BoxV1();

	void Init(const float MBW, const float MBH,
		const float MxW, const float MxH,
		const float MmW, const float MmH, int t, float* R);
	void Update();
	void Render(const int posX, const int posY);

	float posX_;
	float posY_;
	float width_;
	float height_;
	Timer* startEndTimer;
	Timer* holdTimer;
};

class digBox1 {
public:
	digBox1();
	~digBox1();

	void Init(const float SPX, const float SPY,
		const float MBW, const float MBH,
		const float MxW, const float MxH,
		const float MmW, const float MmH, const int t);
	void Update();
	void Render();

	float spawnPosX_;
	float spawnPosY_;
	float width_;
	float height_;
	float boxMixWidth_;
	float boxMixHeight_;
	float boxMinWidth_;
	float boxMinHeight_;
	BoxV1* box[10];
	Timer* bornTimer;

private:
	float Rend_;

};