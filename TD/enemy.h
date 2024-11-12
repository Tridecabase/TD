#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Tools/config.h" 

class Enemy {
public:

	//コンストラクタとデストラクタ
	Enemy();
	~Enemy();

	//敵の初期化
	void Init();
	//敵の移動処理
	void Move();
	//敵の描画
	void Draw();

	// ============================
	// 敵基本情報
	// ============================

	//敵の位置ベクトル
	Vector3 pos;
	//敵の長さ
	float width;
	//敵の深さ
	float depth;
	//敵の高さ
	float height;
	//敵の生存フラグ
	bool isAlive;


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

};