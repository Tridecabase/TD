#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Tools/config.h" 
#include "./Entities/bullet.h"
#include <string>
#include <random>
#include <Novice.h>

//行動IDに基づいたBOSS行動モジュール
enum class ActionID {
	IDLE,					//待機
	MOVE_AND_DEPLOY,		//移動して浮遊砲を設置する行動
	FIRE_AT_PLAYER,			//プレイヤーに向けた弾を多方向に発射
	BREAK_STATE				//ブレイク状態
							//and more...
};


class Enemy {
public:

	//コンストラクタとデストラクタ
	Enemy();
	~Enemy();

	//敵の初期化
	void Init();
	//敵の移動処理
	void Move(BulletA*bulletA, BulletB*bulletB);
	//敵の描画
	void Draw();
	//敵の情報を表示する関数
	void DrawInfo();

	// ============================
	// 敵の攻撃行動関数
	// ============================

	//行動をランダムに選択して実行
	void PerformAction();
	//ダメージを受けた際の処理
	void TakeDamage(int damage);
	//ブレイクゲージを更新
	void UpdateBreakMeter();


	// ============================
	// 敵基本情報
	// ============================

	//BOSSの名前
	std::string name;
	//現在のHP
	int hp;
	//最大HP
	int max_hp;

	//敵の位置ベクトル
	Vector3 pos;
	//敵の長さ
	float width;
	//敵の深さ
	float depth;
	//敵の高さ
	float height;
	//敵の色
	int color;
	//敵の生存フラグ
	bool isAlive;

	//現在の行動
	ActionID current_action;
	//行動の残り時間
	int action_timer;
	//ブレイクゲージ
	int break_meter;
	//ブレイクゲージの最大値
	int break_meter_max;
	//ブレイク状態フラグ
	bool is_break;
	//ブレイク状態の残り時間
	int break_timer;


	float tmp;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	int shootCoolTime;
	//弾丸撃つのフラグ
	bool isShootAble;

	// ============================
	// 背景用のメンバー変数を
	// ============================

	Vector2 screen_pos;


private:

	// ============================
	// 敵の攻撃行動管理
	// ============================

	//行動を切り替える関数
	void SetRandomAction();

	//行動を実行する関数
	//ID 101: 移動して浮遊砲を設置
	void ExecuteMoveAndDeploy(); 
	//ID 102: 弾を多方向に発射
	void ExecuteFireAtPlayer() const;
	//and more...

	// ============================
	// ブレイク状態の管理
	// ============================

	//ブレイク状態に入る
	void EnterBreakState();
	//ブレイク状態を終了
	void ExitBreakState();

};