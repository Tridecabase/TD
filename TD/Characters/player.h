#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Entities/map.h" 
#include "./Tools/config.h" 

class Player {
public:

	//コンストラクタとデストラクタ
	Player();
	~Player();

	//プレイヤーの初期化
	void Init(Map* map);
	//プレイヤーの移動処理
	void Move(Map* map, char keys[256], char preKeys[256]);
	//プレイヤーの描画
	void Draw();

	// ============================
	// プレイヤ基本情報
	// ============================

	//プレイヤーの位置ベクトル
	Vector3 pos;
	Vector2 tmpPos;
	Vector2 posNum;
	//プレイヤーの速度ベクトル
	Vector2 speed;
	//プレイヤーの長さ
	float width;
	//プレイヤーの高さ
	float height;
	//プレイヤーの動きクールタイム
	int moveCooltime;
	//プレイヤーの生存フラグ
	bool isAlive;


	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	int shootCoolTimeA;
	//弾丸撃つのフラグ
	bool isShootAbleA;
	//弾丸のクールダウン
	int shootCoolTimeB;
	//弾丸撃つのフラグ
	bool isShootAbleB;

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