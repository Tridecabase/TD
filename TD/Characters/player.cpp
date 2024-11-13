#include <Novice.h>
#include "player.h" 

//コンストラクタ
Player::Player() {

	// ============================
	// プレイヤ基本情報
	// ============================

	//プレイヤーの位置ベクトル
	pos.x = 192.0f;
	pos.y = 96.0f;
	pos.z = 50.0f;
	posNum.x = 0.0f;
	posNum.y = 0.0f;
	tmpPos.x = 192.0f;
	tmpPos.y = 96.0f;
	//プレイヤーの速度ベクトル
	speed.x = BLOCK_SIZE;
	speed.y = BLOCK_SIZE / 2.0f;
	//プレイヤーの長さ
	width = 40.0f;
	//プレイヤーの高さ
	height = 20.0f;
	//プレイヤーの動きクールタイム
	moveCooltime = 0;
	//プレイヤーの生存フラグ
	isAlive = true;


	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTimeA = 10;
	shootCoolTimeB = 30;
	//弾丸撃つのフラグ
	isShootAbleA = false;
	isShootAbleB = false;

	// ============================
	// 背景用のメンバー変数を
	// ============================

	screen_pos = {};
	

}
//デストラクタ
Player::~Player() {}


////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Player::Init(Map* map) {

	// ============================
	// プレイヤ基本情報
	// ============================

	//プレイヤーの位置ベクトル
	pos.x = 192.0f;
	pos.y = 96.0f;
	pos.z = 50.0f;
	posNum.x = 0.0f;
	posNum.y = 0.0f;
	tmpPos.x = 192.0f;
	tmpPos.y = 96.0f;
	//プレイヤーの速度ベクトル
	speed.x = map->blockSize;
	speed.y = map->blockSize / 2.0f;
	//プレイヤーの長さ
	width = 40.0f;
	//プレイヤーの高さ
	height = 20.0f;
	//プレイヤーの動きクールタイム
	moveCooltime = 0;
	//プレイヤーの生存フラグ
	isAlive = true;


	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTimeA = 10;
	shootCoolTimeB = 30;
	//弾丸撃つのフラグ
	isShootAbleA = false;
	isShootAbleB = false;

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Player::Move(Map* map, char keys[256], char preKeys[256]) {

	posNum.x = pos.x / speed.x;
	posNum.y = pos.y / speed.y;

	tmpPos.x = pos.x;
	tmpPos.y = pos.y;


	if (posNum.y == 3) {
		pos.z = 0.0f;
		width = 48.0f;
		height = 24.0f;
	}
	if (posNum.y == 2) {
		pos.z = 50.0f;
		width = 40.0f;
		height = 20.0f;
	}
	if (posNum.y == 1) {
		pos.z = 100.0f;
		width = 32.0f;
		height = 16.0f;
	}

	if (!preKeys[DIK_W] && keys[DIK_W]) {
		tmpPos.y -= speed.y;
		posNum.y = tmpPos.y / speed.y;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			pos.y = tmpPos.y;
		}
	}
	else if (!preKeys[DIK_S] && keys[DIK_S]) {
		tmpPos.y += speed.y;
		posNum.y = tmpPos.y / speed.y;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			pos.y = tmpPos.y;
		}
	}

	if (moveCooltime >= 0) {
		moveCooltime--;
	}
	if (moveCooltime < 0) {
		moveCooltime = -1;
		if (keys[DIK_A]) {
			tmpPos.x -= speed.x;
			posNum.x = tmpPos.x / speed.x;

			if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
				pos.x = tmpPos.x;
				moveCooltime = 10;
			}
		}
		else if (keys[DIK_D]) {
			tmpPos.x += speed.x;
			posNum.x = tmpPos.x / speed.x;

			if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
				pos.x = tmpPos.x;
				moveCooltime = 10;
			}
		}
	}

	screen_pos.x = map->blockPos.x + pos.x;
	screen_pos.y = map->blockPos.y + pos.y;

}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Player::Draw() {

	//テスト：プレイヤーの描画
	Novice::DrawEllipse(
		static_cast<int>(screen_pos.x),
		static_cast<int>(screen_pos.y),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f, WHITE, kFillModeSolid);
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////