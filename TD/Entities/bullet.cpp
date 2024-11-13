#include <Novice.h>
#include <math.h>
#include "bullet.h"


BulletA::BulletA() {
	pos = {};
	newPos = {};
	frontPos = {};
	screen_pos = {};
	mousePosX = 0;
	mousePosY = 0;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	radius = 20.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	distanceToMouse = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_A; i++) {
		bulletA[i] = { 
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		20.0f,	//radius 
		1.0f,	//scale 
		30.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		0.0f,	//stoppageTime
		0.0f,	//stoppageTimer
		false	//isShoot 
		};
	}
}
BulletA::~BulletA() {}

void BulletA::Init() {
	pos = {};
	newPos = {};
	frontPos = {};
	screen_pos = {};
	mousePosX = 0;
	mousePosY = 0;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	radius = 20.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	distanceToMouse = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_A; i++) {
		bulletA[i] = {
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		20.0f,	//radius 
		1.0f,	//scale 
		30.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		0.0f,	//stoppageTime
		0.0f,	//stoppageTimer
		false	//isShoot 
		};
	}
}

void BulletA::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (player->isPlayerLeft) {
			if (keys[DIK_A]) {
				bulletA[i].mousePosX += static_cast<int>(OUTER_BG_SPEED) / 2;
			}
		}
		if (player->isPlayerRight) {
			if (keys[DIK_D]) {
				bulletA[i].mousePosX -= static_cast<int>(OUTER_BG_SPEED) / 2;
			}
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
				player->shootCoolTimeA = 3;
				for (int i = 0; i < MAX_BULLET_A; i++) {
					if (!bulletA[i].isShoot) {
						bulletA[i].isShoot = true;
						bulletA[i].pos.x = player->pos.x;
						bulletA[i].pos.y = player->pos.y;
						bulletA[i].pos.z = player->pos.z;
						Novice::GetMousePosition(&bulletA[i].mousePosX, &bulletA[i].mousePosY);
						bulletA[i].distanceToMouse = sqrtf(static_cast<float>(
							pow(map->blockPos.x + player->pos.x - bulletA[i].mousePosX, 2) +
							pow(map->blockPos.y + player->pos.y - bulletA[i].mousePosY, 2)));
						bulletA[i].frontPos.x = map->blockPos.x + player->pos.x;
						bulletA[i].frontPos.y = map->blockPos.y + player->pos.y;
						break;
					}
				}
			}
		}
		for (int i = 0; i < MAX_BULLET_A; i++) {
			if (bulletA[i].isShoot) {
				bulletA[i].pos.z += bulletA[i].speed;
				bulletA[i].time += bulletA[i].speed / bulletA[i].distanceToMouse;
				bulletA[i].scale = 1.0f - bulletA[i].pos.z / 1500.0f;
				bulletA[i].newPos.x = (1 - bulletA[i].time) * bulletA[i].frontPos.x + bulletA[i].time * bulletA[i].mousePosX;
				bulletA[i].newPos.y = (1 - bulletA[i].time) * bulletA[i].frontPos.y + bulletA[i].time * bulletA[i].mousePosY;
				if (bulletA[i].time >= 1.0f) {
					bulletA[i].gravityY += bulletA[i].gravitySpeedY;
					bulletA[i].gravitySpeedY += 2.3f;
				}
				if (bulletA[i].pos.z >= 1100.0f || bulletA[i].time >= 3.5f) {
					bulletA[i].isShoot = false;
					bulletA[i].time = 0.0f;
					bulletA[i].gravityY = 0.0f;
					bulletA[i].gravitySpeedY = 0.0f;
				}

				bulletA[i].screen_pos.x = bulletA[i].newPos.x;
				bulletA[i].screen_pos.y = bulletA[i].newPos.y + bulletA[i].gravityY;
			}
		}
	}
}

void BulletA::Draw() const {
	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (bulletA[i].isShoot) {
			Novice::DrawEllipse(static_cast<int>(bulletA[i].screen_pos.x), static_cast<int>(bulletA[i].screen_pos.y), static_cast<int>(bulletA[i].radius * bulletA[i].scale), static_cast<int>(bulletA[i].radius * bulletA[i].scale), 0.0f, BLUE, kFillModeSolid);
		}
	}
}

/// <summary>
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

BulletB::BulletB() {
	pos = {};
	randPos = {};
	newPos = {};
	frontPos = {};
	mousePosX = 0;
	mousePosY = 0;
	distanceToMouse = 0.0f;
	radius = 15.0f;
	scale = 1.0f;
	speed = 100.0f;
	stoppageTime = 0.0f;
	stoppageTimer = 0.0f;
	time = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_B; i++) {
		bulletB[i] = {
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		15.0f,	//radius 
		1.0f,	//scale 
		100.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		0.0f,	//stoppageTime
		0.0f,	//stoppageTimer
		false	//isShoot 
		};
	}
}

BulletB::~BulletB() {}

void BulletB::Init() {
	pos = {};
	randPos = {};
	newPos = {};
	frontPos = {};
	mousePosX = 0;
	distanceToMouse = 0.0f;
	radius = 15.0f;
	scale = 1.0f;
	speed = 100.0f;
	time = 0.0f;
	stoppageTime = 0.0f;
	stoppageTimer = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_B; i++) {
		bulletB[i] = {
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		15.0f,	//radius 
		1.0f,	//scale 
		100.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		0.0f,	//stoppageTime
		0.0f,	//stoppageTimer
		false	//isShoot 
		};
	}
}

void BulletB::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (player->isPlayerLeft) {
			if (keys[DIK_A]) {
				bulletB[i].mousePosX += static_cast<int>(OUTER_BG_SPEED);
				bulletB[i].frontPos.x += static_cast<int>(OUTER_BG_SPEED);
			}
		}
		if (player->isPlayerRight) {
			if (keys[DIK_D]) {
				bulletB[i].mousePosX -= static_cast<int>(OUTER_BG_SPEED);
				bulletB[i].frontPos.x -= static_cast<int>(OUTER_BG_SPEED);
			}
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
				for (int i = 0; i < MAX_BULLET_B; i++) {
					if (!bulletB[i].isShoot) {
						bulletB[i].isShoot = true;
						bulletB[i].pos.x = player->pos.x;
						bulletB[i].pos.y = player->pos.y;
						bulletB[i].pos.z = player->pos.z;
						bulletB[i].randPos.x = (rand() % 101 - 50.0f);
						bulletB[i].randPos.y = (rand() % 100 + 1.0f);
						bulletB[i].randPos.z = (rand() % 101 + 1.0f);
						bulletB[i].stoppageTime = (80.0f + rand() % 31);
						Novice::GetMousePosition(&bulletB[i].mousePosX, &bulletB[i].mousePosY);
						bulletB[i].distanceToMouse = sqrtf(static_cast<float>(
							pow(map->blockPos.x + player->pos.x - bulletB[i].mousePosX, 2) +
							pow(map->blockPos.y + player->pos.y - bulletB[i].mousePosY, 2)));
						bulletB[i].frontPos.x = map->blockPos.x + player->pos.x;
						bulletB[i].frontPos.y = map->blockPos.y + player->pos.y;
					}
				}
			}
		}
		for (int i = 0; i < MAX_BULLET_B; i++) {
			if (bulletB[i].isShoot) {
				bulletB[i].scale = 1.0f - bulletB[i].pos.z / 3000.0f;
				bulletB[i].stoppageTimer++;
				bulletB[i].newPos.x = (1 - bulletB[i].time) * bulletB[i].frontPos.x + bulletB[i].time * bulletB[i].mousePosX;
				bulletB[i].newPos.y = (1 - bulletB[i].time) * bulletB[i].frontPos.y + bulletB[i].time * bulletB[i].mousePosY;
				if (bulletB[i].stoppageTimer <= bulletB[i].stoppageTime) {
					bulletB[i].frontPos.x -= bulletB[i].randPos.x / 48.0f;
					bulletB[i].frontPos.y -= bulletB[i].randPos.y / 48.0f;
					bulletB[i].pos.z -= bulletB[i].randPos.z / 5.0f;
				}
				else {
					bulletB[i].pos.z += bulletB[i].speed + bulletB[i].randPos.z / 4.0f;
					bulletB[i].time += bulletB[i].speed / (bulletB[i].distanceToMouse * 3);
					if (bulletB[i].time > 1.1f) {
						bulletB[i].isShoot = false;
						bulletB[i].time = 0.0f;
						bulletB[i].stoppageTimer = 0.0f;
					}
				}

				bulletB[i].screen_pos.x = bulletB[i].newPos.x;
				bulletB[i].screen_pos.y = bulletB[i].newPos.y;
			}
		}
	}
}

void BulletB::Draw() const {
	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (bulletB[i].isShoot) {
			Novice::DrawEllipse(static_cast<int>(bulletB[i].screen_pos.x), static_cast<int>(bulletB[i].screen_pos.y), static_cast<int>(bulletB[i].radius * bulletB[i].scale), static_cast<int>(bulletB[i].radius * bulletB[i].scale), 0.0f, RED, kFillModeSolid);
		}
	}
}
