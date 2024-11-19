#include <Novice.h>
#include <math.h>
#include "bullet.h"


BulletA::BulletA() {
	pos = {};
	savePos = {};
	newPos = {};
	frontPos = {};
	lastPos = {};
	screen_pos = {};
	shadowPos = {};
	mousePosX = 0;
	mousePosY = 0;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	radius = 20.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	distanceToMouse = 0.0f;
	altitude = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_A; i++) {
		bulletA[i] = { 
		{},		//pos
		{},		//randPos
		{},		//savePos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos 
		{},		//shadowPos 
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
		0.0f,	//altitude
		0.0f,	//frontAltitude
		false	//isShoot 
		};
	}
}
BulletA::~BulletA() {}

void BulletA::Init() {
	pos = {};
	newPos = {};
	frontPos = {};
	lastPos = {};
	screen_pos = {};
	shadowPos = {};
	mousePosX = 0;
	mousePosY = 0;
	gravityY = 0.0f;
	gravitySpeedY = 0.0f;
	radius = 20.0f;
	scale = 1.0f;
	speed = 30.0f;
	time = 0.0f;
	distanceToMouse = 0.0f;
	altitude = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_A; i++) {
		bulletA[i] = {
		{},		//pos
		{},		//randPos
		{},		//savePos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos 
		{},		//shadowPos 
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
		0.0f,	//altitude
		0.0f,	//frontAltitude
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

void BulletA::Shot(Player* player) {
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
						bulletA[i].savePos.z = player->pos.z;
						Novice::GetMousePosition(&bulletA[i].mousePosX, &bulletA[i].mousePosY);
						bulletA[i].distanceToMouse = sqrtf(static_cast<float>(
							pow(player->screen_pos.x - bulletA[i].mousePosX, 2) +
							pow(player->screen_pos.y - bulletA[i].mousePosY, 2)));
						bulletA[i].frontPos.x = player->screen_pos.x;
						bulletA[i].frontPos.y = player->screen_pos.y;
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
				bulletA[i].altitude += bulletA[i].pos.z / 150.0f; //bulletA[i].pos.z / 7.0f;
				bulletA[i].newPos.x = (1 - bulletA[i].time) * bulletA[i].frontPos.x + bulletA[i].time * bulletA[i].mousePosX;
				bulletA[i].newPos.y = (1 - bulletA[i].time) * bulletA[i].frontPos.y + bulletA[i].time * bulletA[i].mousePosY;
				if (bulletA[i].time >= 1.0f) {
					bulletA[i].gravityY += bulletA[i].gravitySpeedY;
					bulletA[i].gravitySpeedY += 2.3f;
				}
				if (bulletA[i].pos.z > 1100.0f) {
					bulletA[i].isShoot = false;
					bulletA[i].time = 0.0f;
					bulletA[i].gravityY = 0.0f;
					bulletA[i].gravitySpeedY = 0.0f;
					bulletA[i].altitude = 0.0f;
				}

				bulletA[i].lastPos = getLastPos(bulletA[i].savePos.z, bulletA[i].speed, bulletA[i].distanceToMouse, bulletA[i].frontPos.x, bulletA[i].frontPos.y, bulletA[i].mousePosX, bulletA[i].mousePosY);
				bulletA[i].screen_pos.x = bulletA[i].newPos.x;
				bulletA[i].screen_pos.y = bulletA[i].newPos.y + bulletA[i].gravityY;
				bulletA[i].shadowPos = getShadowPos(bulletA[i].frontPos, bulletA[i].lastPos, bulletA[i].screen_pos);
				bulletA[i].shadowPos.y += bulletA[i].altitude;
			}
			else {
				bulletA[i].screen_pos = { NULL };
			}
		}
	}
}

void BulletA::Draw() const {
	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (bulletA[i].isShoot) {
		/*	Novice::DrawEllipse(static_cast<int>(bulletA[i].shadowPos.x), static_cast<int>(bulletA[i].shadowPos.y), static_cast<int>(bulletA[i].radius * bulletA[i].scale), static_cast<int>(bulletA[i].radius * bulletA[i].scale), 0.0f, BLACK, kFillModeSolid);*/
			Novice::DrawEllipse(static_cast<int>(bulletA[i].lastPos.x), static_cast<int>(bulletA[i].lastPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, 0x4bbc54FF, kFillModeWireFrame);
		}
	}
	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (bulletA[i].isShoot) {
			Novice::DrawEllipse(static_cast<int>(bulletA[i].screen_pos.x), static_cast<int>(bulletA[i].screen_pos.y), static_cast<int>(bulletA[i].radius * bulletA[i].scale), static_cast<int>(bulletA[i].radius * bulletA[i].scale), 0.0f, BLUE, kFillModeSolid);
		}
	}
	Novice::ScreenPrintf(100, 200, "bulletA.pos.z = %f,%f", bulletA[0].pos.z, bulletA[0].lastPos.y);
	Novice::ScreenPrintf(100, 220, "%d,%d", bulletA[0].mousePosX, bulletA[0].mousePosY);
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
	speed = 110.0f;
	stoppageTime = 0.0f;
	stoppageTimer = 0.0f;
	time = 0.0f;
	altitude = 0.0f;
	frontAltitude = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_B; i++) {
		bulletB[i] = {
		{},		//pos
		{},		//randPos
		{},		//savePos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos 
		{},		//shadowPos 
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		15.0f,	//radius 
		1.0f,	//scale 
		110.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		0.0f,	//stoppageTime
		0.0f,	//stoppageTimer
		0.0f,	//altitude
		0.0f,	//frontAltitude
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
	speed = 110.0f;
	time = 0.0f;
	stoppageTime = 0.0f;
	stoppageTimer = 0.0f;
	altitude = 0.0f;
	frontAltitude = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_B; i++) {
		bulletB[i] = {
		{},		//pos
		{},		//randPos
		{},		//savePos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos 
		{},		//shadowPos 
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		15.0f,	//radius 
		1.0f,	//scale 
		110.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		0.0f,	//stoppageTime
		0.0f,	//stoppageTimer
		0.0f,	//altitude
		0.0f,	//frontAltitude
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

void BulletB::Shot(Player* player) {
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
						bulletB[i].randPos.y = (rand() % 80 + 1.0f);
						bulletB[i].randPos.z = (rand() % 101 + 1.0f);
						bulletB[i].stoppageTime = (80.0f + rand() % 31);
						Novice::GetMousePosition(&bulletB[i].mousePosX, &bulletB[i].mousePosY);
						bulletB[i].distanceToMouse = sqrtf(static_cast<float>(
							pow(player->screen_pos.x - bulletB[i].mousePosX, 2) +
							pow(player->screen_pos.y - bulletB[i].mousePosY, 2)));
						bulletB[i].frontPos.x = player->screen_pos.x;
						bulletB[i].frontPos.y = player->screen_pos.y;
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
					bulletB[i].pos.z -= bulletB[i].randPos.z / 48.0f;
					bulletB[i].frontAltitude += bulletB[i].randPos.y / 32.0f;
				}
				else {
					bulletB[i].pos.z += bulletB[i].speed + bulletB[i].randPos.z / 96.0f;
					bulletB[i].time += bulletB[i].speed / (bulletB[i].distanceToMouse * 3);
					bulletB[i].altitude += bulletB[i].pos.z / 150.0f; //bulletA[i].pos.z / 7.0f;
					if (bulletB[i].time > 1.05f) {
						bulletB[i].isShoot = false;
						bulletB[i].time = 0.0f;
						bulletB[i].stoppageTimer = 0.0f;
						bulletB[i].altitude = 0.0f;
						bulletB[i].frontAltitude = 0.0f;
					}
				}
				bulletB[i].lastPos = { static_cast<float>(bulletB[i].mousePosX) , static_cast<float>(bulletB[i].mousePosY)};
				bulletB[i].screen_pos.x = bulletB[i].newPos.x;
				bulletB[i].screen_pos.y = bulletB[i].newPos.y;
				bulletB[i].shadowPos = getShadowPos(bulletB[i].frontPos, bulletB[i].lastPos, bulletB[i].screen_pos, bulletB[i].frontAltitude);
				bulletB[i].shadowPos.y += bulletB[i].altitude;
			}
			else {
				bulletB[i].screen_pos = { NULL };
			}
		}
	}
}

void BulletB::Draw() const {
	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (bulletB[i].isShoot) {
		/*	Novice::DrawEllipse(static_cast<int>(bulletB[i].shadowPos.x), static_cast<int>(bulletB[i].shadowPos.y), static_cast<int>(bulletB[i].radius * bulletB[i].scale), static_cast<int>(bulletB[i].radius * bulletB[i].scale), 0.0f, BLACK, kFillModeSolid);*/
			Novice::DrawEllipse(static_cast<int>(bulletB[i].lastPos.x), static_cast<int>(bulletB[i].lastPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, 0x4bbc54FF, kFillModeWireFrame);
		}
	}
	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (bulletB[i].isShoot) {
			Novice::DrawEllipse(static_cast<int>(bulletB[i].screen_pos.x), static_cast<int>(bulletB[i].screen_pos.y), static_cast<int>(bulletB[i].radius * bulletB[i].scale), static_cast<int>(bulletB[i].radius * bulletB[i].scale), 0.0f, GREEN, kFillModeSolid);
		}
	}
	Novice::ScreenPrintf(100, 240, "bulletB.pos.Z = %f,bulletB.altitude = %f", bulletB[0].pos.z, bulletB[0].altitude);
}