#include <Novice.h>
#include <math.h>
#include "bullet.h"


Bullet::Bullet() {
	pos.x = 0.0f;
	pos.y = 0.0f;
	mousePosX = 0;
	mousePosY = 0;
	width = 45.0f;
	height = 45.0f;
	radius = 3.0f;
	speed = 8.0f;
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
				player->shootCoolTime = 10;
				if (!isShoot) {
					isShoot = true;
					pos.x = player->pos.x;
					pos.y = player->pos.y;
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
			time += 20.0f / distanceToMouse;
			newPos.x = (1 - time) * frontPos.x + time * mousePosX;
			newPos.y = (1 - time) * frontPos.y + time * mousePosY;
			if (newPos.y <= mousePosY) {
				isShoot = false;
				time = 0.0f;
			}
		}
	}
}

void Bullet::Draw() {
	Novice::DrawEllipse(static_cast<int>(newPos.x), static_cast<int>(newPos.y), static_cast<int>(width), static_cast<int>(height), 0.0, BLUE, kFillModeSolid);
}
