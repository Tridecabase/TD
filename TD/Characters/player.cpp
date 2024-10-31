#include <Novice.h>
#include "player.h" 

Player::Player() {

	pos.x = 192.0f;
	pos.y = 96.0f;
	posNum.x = 0.0f;
	posNum.y = 0.0f;
	tmpPos.x = 192.0f;
	tmpPos.y = 96.0f;
	speed.x = BLOCK_SIZE;
	speed.y = BLOCK_SIZE / 2.0f;
	width = 40.0f;
	height = 20.0f;

	shootCoolTime = 10;
	isShootAble = false;

	isAlive = true;
}
Player::~Player(){}

void Player::Init(Map* map) {
	pos.x = 192.0f;
	pos.y = 96.0f;
	posNum.x = 0.0f;
	posNum.y = 0.0f;
	tmpPos.x = 192.0f;
	tmpPos.y = 96.0f;
	speed.x = map->blockSize;
	speed.y = map->blockSize / 2.0f;
	width = 40.0f;
	height = 20.0f;

	shootCoolTime = 10;
	isShootAble = false;

	isAlive = true;
};

void Player::Move(Map* map, char keys[256], char preKeys[256]) {


	posNum.x = pos.x / speed.x;
	posNum.y = pos.y / speed.y;

	tmpPos.x = pos.x;
	tmpPos.y = pos.y;

	if (posNum.y == 2) {
		width = 40.0f;
		height = 20.0f;
	}
	if (posNum.y == 3) {
		width = 48.0f;
		height = 24.0f;
	}
	if (posNum.y == 1) {
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
	else if (!preKeys[DIK_A] && keys[DIK_A]) {
		tmpPos.x -= speed.x;
		posNum.x = tmpPos.x / speed.x;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			pos.x = tmpPos.x;
		}
	}
	else if (!preKeys[DIK_D] && keys[DIK_D]) {
		tmpPos.x += speed.x;
		posNum.x = tmpPos.x / speed.x;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			pos.x = tmpPos.x;
		}
	}
}

void Player::Draw(Map* map) {
	Novice::DrawEllipse(static_cast<int>(map->blockPos.x + pos.x), static_cast<int>(map->blockPos.y + pos.y), static_cast<int>(width), static_cast<int>(height), 0.0f, WHITE, kFillModeSolid);
}