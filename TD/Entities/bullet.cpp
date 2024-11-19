<<<<<<< Updated upstream
=======
#include <Novice.h>
#include <math.h>
#include "bullet.h"


BulletA::BulletA() {
	newPos = {};
	frontPos = {};
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	mousePosX = 0;
	mousePosY = 0;
	distanceToMouse = 0.0f;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	width = 20.0f;
	height = 20.0f;
	depth = 20.0f;
	radius = 3.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	maxBullet = 32;
	isShoot = false;

	screen_pos = {};
}
BulletA::~BulletA() {}

void BulletA::Init() {
	newPos = {};
	frontPos = {};
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	mousePosX = 0;
	mousePosY = 0;
	distanceToMouse = 0.0f;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	width = 20.0f;
	height = 20.0f;
	depth = 20.0f;
	radius = 3.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	maxBullet = 32;
	isShoot = false;

	screen_pos = {};
}

void BulletA::Scroll(Player* player, char keys[256]) {
	if (player->isPlayerLeft) {
		if (keys[DIK_A]) {
			//遷移量*深さ係数
			//今のはマジックナンバー、後で直す
			mousePosX += static_cast<int>((OUTER_BG_SPEED) / 2 * (depth / 20.0f));
		}
	}
	if (player->isPlayerRight) {
		if (keys[DIK_D]) {
			//遷移量*深さ係数
			//今のはマジックナンバー、後で直す
			mousePosX -= static_cast<int>((OUTER_BG_SPEED) / 2 * (depth / 20.0f));
		}
	}
}

void BulletA::Shot(Player* player, Map* map) {
	if (player->isAlive) {
		if (player->shootCoolTimeA > 0) {
			player->shootCoolTimeA--;
		}
		else {
			player->isShootAbleA = true;
		}
		if (Novice::IsPressMouse(0)) {
			if (player->isShootAbleA) {
				player->isShootAbleA = false;
				player->shootCoolTimeA = 30;
				if (!isShoot) {
					isShoot = true;
					pos.x = player->pos.x;
					pos.y = player->pos.y;
					pos.z = player->pos.z;
					Novice::GetMousePosition(&mousePosX, &mousePosY);
					distanceToMouse = sqrtf(static_cast<float>(
						pow(map->blockPos.x + player->pos.x - mousePosX, 2) +
						pow(map->blockPos.y + player->pos.y - mousePosY, 2)));
					frontPos.x = map->blockPos.x + player->pos.x;
					frontPos.y = map->blockPos.y + player->pos.y;
				}

			}
		}
		if (isShoot) {
			pos.z += speed;
			time += speed / distanceToMouse;
			scale = 1.0f - pos.z / 1800.0f;
			newPos.x = (1 - time) * frontPos.x + time * mousePosX;
			newPos.y = (1 - time) * frontPos.y + time * mousePosY;
			if (time >= 1.2f) {
				gravityY += gravitySpeedY;
				gravitySpeedY += 2.0f;
			}
			if (pos.z >= 1300.0f || time >= 4.0f) {
				isShoot = false;
				time = 0.0f;
				gravityY = 0.0f;
				gravitySpeedY = 0.0f;
			}
		}
	}

	screen_pos.x = newPos.x;
	screen_pos.y = newPos.y + gravityY;
}

void BulletA::Draw() const {
	if (isShoot) {
		Novice::DrawEllipse(static_cast<int>(screen_pos.x), static_cast<int>(screen_pos.y), static_cast<int>(width * scale), static_cast<int>(height * scale), 0.0, BLUE, kFillModeSolid);
	}

	Novice::ScreenPrintf(100, 100, "%f", pos.z);
	Novice::ScreenPrintf(100, 120, "%f", depth);

}

/// <summary>
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

BulletB::BulletB() {
	newPos = {};
	frontPos = {};
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	randPos.x = 0.0f;
	randPos.y = 0.0f;
	randPos.z = 0.0f;
	mousePosX = 0;
	mousePosY = 0;
	distanceToMouse = 0.0f;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	width = 15.0f;
	height = 15.0f;
	depth = 15.0f;
	radius = 3.0f;
	scale = 1.0f;
	speed = 120.0f;
	stoppageTime = 0.0f;
	time = 0.0f;
	maxBullet = 32;

	isShoot = false;

	screen_pos = {};
}

BulletB::~BulletB() {}

void BulletB::Init() {
	newPos = {};
	frontPos = {};
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	randPos.x = 0.0f;
	randPos.y = 0.0f;
	randPos.z = 0.0f;
	mousePosX = 0;
	distanceToMouse = 0.0f;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	width = 15.0f;
	height = 15.0f;
	depth = 15.0f;
	radius = 3.0f;
	scale = 1.0f;
	speed = 120.0f;
	time = 0.0f;
	stoppageTime = 0.0f;
	maxBullet = 32;
	isShoot = false;

	screen_pos = {};
}

void BulletB::Scroll(Player* player, char keys[256]) {
	if (player->isPlayerLeft) {
		if (keys[DIK_A]) {
			mousePosX += static_cast<int>(OUTER_BG_SPEED);
		}
	}
	if (player->isPlayerRight) {
		if (keys[DIK_D]) {
			mousePosX -= static_cast<int>(OUTER_BG_SPEED);
		}
	}
}

void BulletB::Shot(Player* player, Map* map) {
	if (player->isAlive) {
		if (player->shootCoolTimeB > 0) {
			player->shootCoolTimeB--;
		}
		else {
			player->isShootAbleB = true;
		}
		if (Novice::IsPressMouse(1)) {
			if (player->isShootAbleB) {
				player->isShootAbleB = false;
				player->shootCoolTimeB = 30;
				if (!isShoot) {
					isShoot = true;
					pos.x = player->pos.x;
					pos.y = player->pos.y;
					pos.z = player->pos.z;
					randPos.x = (rand() % 101) - 50.0f;
					randPos.y = (rand() % 100 + 1.0f);
					randPos.z = (rand() % 76 - 35.0f);
					Novice::GetMousePosition(&mousePosX, &mousePosY);
					distanceToMouse = sqrtf(static_cast<float>(
						pow(map->blockPos.x + player->pos.x - mousePosX, 2) +
						pow(map->blockPos.y + player->pos.y - mousePosY, 2)));
					frontPos.x = map->blockPos.x + player->pos.x;
					frontPos.y = map->blockPos.y + player->pos.y;
				}

			}
		}
		if (isShoot) {
			scale = 1.0f - pos.z / 3000.0f;
			stoppageTime++;
			newPos.x = (1 - time) * frontPos.x + time * mousePosX;
			newPos.y = (1 - time) * frontPos.y + time * mousePosY;
			if (stoppageTime <= 70.0f) {
				frontPos.x -= randPos.x/50.0f;
				frontPos.y -= randPos.y/50.0f;
				pos.z -= randPos.z/10.0f;
			}
			else {
				pos.z += speed;
				time += speed / (distanceToMouse * 2);
				if (time > 1.1f) {
					isShoot = false;
					time = 0.0f;
					stoppageTime = 0.0f;
				}
			}
		}
	}

	screen_pos.x = newPos.x;
	screen_pos.y = newPos.y;
}

void BulletB::Draw() const {
	if (isShoot) {
		Novice::DrawEllipse(static_cast<int>(screen_pos.x), static_cast<int>(screen_pos.y), static_cast<int>(width * scale), static_cast<int>(height * scale), 0.0, RED, kFillModeSolid);

	}
	Novice::ScreenPrintf(100, 180, "%f", pos.z);
}
>>>>>>> Stashed changes
