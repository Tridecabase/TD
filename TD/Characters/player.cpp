#include <Novice.h>
#include "player.h" 

//コンストラクタ
Player::Player() {

	// ============================
	// プレイヤ基本情報
	// ============================

	//プレイヤーの位置ベクトル
	pos.x = BLOCK_SIZE * 2.0f;
	pos.y = BLOCK_SIZE;
	pos.z = 50.0f;
	posNum.x = 0.0f;
	posNum.y = 0.0f;
	tmpPos.x = 0.0f;
	tmpPos.y = 0.0f;
	blockPos.x = BLOCK_SIZE * 2.0f;
	blockPos.y = BLOCK_SIZE;
	//プレイヤーの速度ベクトル
	speed.x = BLOCK_SIZE;
	speed.y = BLOCK_SIZE;
	//プレイヤーの長さ
	width = 40.0f;
	//プレイヤーの高さ
	height = 20.0f;
	//プレイヤーの動きクールタイム
	moveCooltime = 0;
	//プレイヤーの生存フラグ
	isAlive = true;

	isPlayerLeft = false;
	isPlayerRight = false;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTimeA = 3;
	shootCoolTimeB = 500;
	shootCoolTimeC = 5;
	//弾丸撃つのフラグ
	isShootAbleA = false;
	isShootAbleB = false;
	isShootAbleC = false;

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
	pos.x = map->blockSize * 2.0f;
	pos.y = map->blockSize;
	pos.z = 50.0f;
	posNum.x = 0.0f;
	posNum.y = 0.0f;
	tmpPos.x = 0.0f;
	tmpPos.y = 0.0f;
	blockPos.x = map->blockSize * 2.0f;
	blockPos.y = map->blockSize;
	//プレイヤーの速度ベクトル
	speed.x = map->blockSize;
	speed.y = map->blockSize;
	//プレイヤーの長さ
	width = 40.0f;
	//プレイヤーの高さ
	height = 20.0f;
	//プレイヤーの動きクールタイム
	moveCooltime = 0;
	//プレイヤーの生存フラグ
	isAlive = true;

	isPlayerLeft = false;
	isPlayerRight = false;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTimeA = 3;
	shootCoolTimeB = 500;
	shootCoolTimeC = 5;
	//弾丸撃つのフラグ
	isShootAbleA = false;
	isShootAbleB = false;
	isShootAbleC = false;

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Player::Move(Map* map, char keys[256], char preKeys[256]) {

	posNum.x = blockPos.x / speed.x;
	posNum.y = blockPos.y / speed.y;

	tmpPos.x = blockPos.x;
	tmpPos.y = blockPos.y;


	if (posNum.y == 3) {
		pos.y = 52.0f;
		pos.z = 0.0f;
		width = 48.0f;
		height = 24.0f;
		if (posNum.x == 3) {
			pos.x = 120.0f;
		}
		if (posNum.x == 2) {
			pos.x = 0.0f;
		}
		if (posNum.x == 1) {
			pos.x = -120.0f;
		}
	}
	if (posNum.y == 2) {
		pos.y = 0.0f;
		pos.z = 50.0f;
		width = 40.0f;
		height = 20.0f;
		if (posNum.x == 3) {
			pos.x = 106.0f;
		}
		if (posNum.x == 2) {
			pos.x = 0.0f;
		}
		if (posNum.x == 1) {
			pos.x = -107.0f;
		}
	}
	if (posNum.y == 1) {
		pos.y = -46.0f;
		pos.z = 100.0f;
		width = 32.0f;
		height = 16.0f;
		if (posNum.x == 3) {
			pos.x = 91.0f;
		}
		if (posNum.x == 2) {
			pos.x = 0.0f;
		}
		if (posNum.x == 1) {
			pos.x = -93.0f;
		}
	}

	if (!preKeys[DIK_W] && keys[DIK_W]) {
		tmpPos.y -= speed.y;
		posNum.y = tmpPos.y / speed.y;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			blockPos.y = tmpPos.y;
		}
	}
	if (!preKeys[DIK_S] && keys[DIK_S]) {
		tmpPos.y += speed.y;
		posNum.y = tmpPos.y / speed.y;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			blockPos.y = tmpPos.y;
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
				blockPos.x = tmpPos.x;
				moveCooltime = 10;
			}
		}
		else if (keys[DIK_D]) {
			tmpPos.x += speed.x;
			posNum.x = tmpPos.x / speed.x;

			if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
				blockPos.x = tmpPos.x;
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

	Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4/3),
		static_cast<int>(screen_pos.y - height), static_cast<int>(10.0f),
		static_cast<int>((50 -shootCoolTimeB / 10)* height/25),
		0.0f, 0xB961F2FF, kFillModeSolid);
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////