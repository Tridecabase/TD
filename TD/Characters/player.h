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
	void Draw(int color) const;

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


	/*他のcppにplayer.cppの情報を渡す関数
	*例：
	* stage.cppの中
	* 宣言の時:
	* Vector2 playerSpeed;
	* 初期化の時:
	* playerSpeed = {};
	* 更新処理の時(Stage::Update()の中):
	* playerSpeed = player->GetPlayerSpeed();
	*/
	////プレイヤーの位置ベクトル
	//Vector2 GetPlayerPos() const { return pos; }
	////プレイヤーの速度ベクトル
	//Vector2 GetPlayerSpeed() const { return speed; }

private:

}; 