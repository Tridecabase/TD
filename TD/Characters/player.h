#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <math.h>
#include "./Entities/map.h" 
#include "./Tools/config.h" 
#include "drawPolygon.h"


class Player {
public:

	//コンストラクタとデストラクタ
	Player();
	~Player();

	//プレイヤーの初期化
	void Init(Map* map);
	void InitDisplay();
	//プレイヤーの移動処理
	void Move(Map* map, char keys[256], char preKeys[256]);
	//プレイヤーの描画
	void Draw(const int color, const bool Flat) const;

	// ============================
	// プレイヤ基本情報
	// ============================

	//プレイヤーの位置ベクトル
	Vector3 pos;
	Vector2 tmpPos;
	Vector2 posNum;
	Vector2 blockPos;
	//プレイヤーの速度ベクトル
	Vector2 speed;
	//プレイヤーの長さ
	float width;
	//プレイヤーの高さ
	float height;
	//プレイヤーの動きクールタイム
	int moveCooltime;
	//プレイヤーの無敵時間
	int graceTime;
	//プレイヤーのHP
	int hp;
	//プレイヤーの色
	int color1;
	//プレイヤーの生存フラグ
	bool isAlive;
	//プレイヤーのあたりフラグ
	bool isHit;
	//アニメタイマー
	int clock;
	int timer;
	int velocity;

	bool isPlayerLeft;
	bool isPlayerRight;

	//表示用
	int mouseValue;
	bool mouseType;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	int shootCoolTimeA;
	int shootCoolTimeB;
	int shootCoolTimeC;
	int shootCoolTimeD;
	//弾丸撃つのフラグ
	bool isShootAbleA;
	bool isShootAbleB;
	bool isShootAbleC;
	bool isShootAbleD;


	// ============================
	// 背景用のメンバー変数を
	// ============================

	Vector2 screen_pos;

private:

}; 