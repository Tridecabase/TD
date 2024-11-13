﻿#include <Novice.h>
#include "enemy.h" 

//コンストラクタ
Enemy::Enemy() {

	// ============================
	// 敵基本情報
	// ============================

	//敵の位置ベクトル
	pos.x = 640.0f;
	pos.y = 100.0f;
	pos.z = 1200.0f;
	//敵の長さ
	width = 40.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
	//敵の色
	color = WHITE;
	//敵の生存フラグ
	isAlive = true;

	tmp = 0.0f;


	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTime = 10;
	//弾丸撃つのフラグ
	isShootAble = false;

	// ============================
	// 背景用のメンバー変数を
	// ============================

	screen_pos = {};


}
//デストラクタ
Enemy::~Enemy() {}


////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Init() {

	// ============================
	// 敵基本情報
	// ============================

	//敵の位置ベクトル
	pos.x = 640.0f;
	pos.y = 100.0f;
	pos.z = 1200.0f;
	//敵の長さ
	width = 40.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
	//敵の色
	color = WHITE;
	//敵の生存フラグ
	isAlive = true;

	tmp = 0.0f;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTime = 10;
	//弾丸撃つのフラグ
	isShootAble = false;

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Move(BulletA* bulletA,BulletB* bulletB) {

	color = WHITE;

	if (pos.x + width / 2 >= bulletA->screen_pos.x - bulletA->width / 2 &&
		pos.x - width / 2 <= bulletA->screen_pos.x + bulletA->width / 2) {
		if (pos.y + height / 2 >= bulletA->screen_pos.y - bulletA->height / 2 &&
			pos.y - height / 2 <= bulletA->screen_pos.y + bulletA->height / 2) {
			if (pos.z + depth / 2 >= bulletA->pos.z - bulletA->depth / 2 &&
				pos.z - depth / 2 <= bulletA->pos.z + bulletA->depth / 2) {
				tmp = bulletA->pos.z;
				color = BLACK;
			}
		}
	}

	if (pos.x + width / 2 >= bulletB->screen_pos.x - bulletB->width / 2 &&
		pos.x - width / 2 <= bulletB->screen_pos.x + bulletB->width / 2) {
		if (pos.y + height / 2 >= bulletB->screen_pos.y - bulletB->height / 2 &&
			pos.y - height / 2 <= bulletB->screen_pos.y + bulletB->height / 2) {
				color = BLACK;
		}
	}
	

	screen_pos.x = pos.x;
	screen_pos.y = pos.y;

}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Draw() {

	//テスト：敵の描画
	Novice::DrawBox(
		static_cast<int>(screen_pos.x - width / 2),
		static_cast<int>(screen_pos.y - height / 2),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f, color, kFillModeSolid);

	Novice::ScreenPrintf(100, 140, "%f", tmp);
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////