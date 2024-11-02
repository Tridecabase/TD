#include <Novice.h>
#include <math.h>
#include "bullet.h"


Bullet::Bullet() {
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
	radius = 3.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	maxBullet = 32;
	isShoot = false;
}
Bullet::~Bullet() {
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
	radius = 3.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	maxBullet = 32;
	isShoot = false;
}

void Bullet::Shot(Player* player, Map *map) {
	if (player->isAlive) {
		if (player->shootCoolTime > 0) {
			player->shootCoolTime--;
		}
		else {
			player->isShootAble = true;
		}
		if (Novice::IsPressMouse(0)) {
			if (player->isShootAble) {
				player->isShootAble = false;
				player->shootCoolTime = 30;
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
			scale = 1.0f - pos.z / 1300.0f;
			newPos.x = (1 - time) * frontPos.x + time * mousePosX;
			newPos.y = (1 - time) * frontPos.y + time * mousePosY;
			if (time >= 1.0f) {
				gravityY += gravitySpeedY;
				gravitySpeedY += 3.5f;
			}
			if (pos.z >= 1000.0f) {
				isShoot = false;
				time = 0.0f;
				gravityY = 0.0f;
				gravitySpeedY = 0.0f;
			}
		}
		
	}
}

void Bullet::Draw() const {
	if (isShoot) {
		Novice::DrawEllipse(static_cast<int>(newPos.x), static_cast<int>(newPos.y + gravityY), static_cast<int>(width * scale), static_cast<int>(height * scale), 0.0, BLUE, kFillModeSolid);
	}
	
	Novice::ScreenPrintf(100, 100, "%f", pos.z);
	
}
