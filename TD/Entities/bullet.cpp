#include <Novice.h>
#include <math.h>
#include "bullet.h"

Bullet::Bullet() {
	mouseValue = 0;
	mouseType = false;
}

Bullet::~Bullet() {}

void Bullet::Init() {
	mouseValue = 0;
	mouseType = false;
}

void Bullet::Update() {
	mouseValue += Novice::GetWheel();
	if (mouseValue > 550 || mouseValue < -550) {
		mouseValue = 0;
		if (mouseType) {
			mouseType = false;
		}
		else {
			mouseType = true;
		}
	}
}

BulletA::BulletA() {
	for (int i = 0; i < MAX_BULLET_A; i++) {
		bulletA[i] = {
		{},		//pos
		{},		//savePos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		5.0f,	//radiusX
		12.0f,	//radiusY
		0.0f,	//theta
		1.0f,	//scale 
		30.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		false	//isShoot 
		};
	}
}

BulletA::~BulletA() {}

void BulletA::Init() {
	for (int i = 0; i < MAX_BULLET_A; i++) {
		bulletA[i] = {
		{},		//pos
		{},		//savePos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos
		0,		//mousePosX 
		0,		//mousePosY 
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		5.0f,	//radiusX
		12.0f,	//radiusY
		0.0f,	//theta
		1.0f,	//scale 
		30.0f,	//speed
		0.0f,	//time
		0.0f,	//distanceToMouse
		false	//isShoot 
		};
	}

	playHandle = -1;
	gunA_hanlde = Novice::LoadAudio("../Resources/Sounds/effects/gun_A.mp3");
}

void BulletA::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (player->isPlayerLeft) {
			if (keys[DIK_A]) {
				bulletA[i].mousePosX += static_cast<int>(OUTER_BG_SPEED * (1100.0f - bulletA[i].pos.z) / 1100.0f);
			}
		}
		if (player->isPlayerRight) {
			if (keys[DIK_D]) {
				bulletA[i].mousePosX -= static_cast<int>(OUTER_BG_SPEED * (1100.0f - bulletA[i].pos.z) / 1100.0f);
			}
		}
	}
}

void BulletA::Shot(Player* player, Bullet* bullet) {
	if (player->isAlive) {
		if (player->shootCoolTimeA > 0) {
			player->shootCoolTimeA--;
		}
		else {
			player->isShootAbleA = true;
		}
		if (bullet->mouseType == false) {
			if (Novice::IsPressMouse(0)) {
				if (player->isShootAbleA) {
					player->isShootAbleA = false;
					player->shootCoolTimeA = 3;
					for (int i = 0; i < MAX_BULLET_A; i++) {
						if (!bulletA[i].isShoot) {
							/////////////////////////////BGM
							if (!Novice::IsPlayingAudio(playHandle) || playHandle == -1) {
								playHandle = Novice::PlayAudio(gunA_hanlde, 0, 1.0f);
							}
							else {
								playHandle = Novice::PlayAudio(gunA_hanlde, 0, 1.0f);
							}
							bulletA[i].isShoot = true;
							bulletA[i].pos.x = player->pos.x;
							bulletA[i].pos.y = player->pos.y;
							bulletA[i].pos.z = player->pos.z;
							bulletA[i].savePos.z = player->pos.z;
							bulletA[i].time = 0.0f;
							bulletA[i].gravityY = 0.0f;
							bulletA[i].gravitySpeedY = 0.0f;
							Novice::GetMousePosition(&bulletA[i].mousePosX, &bulletA[i].mousePosY);
							bulletA[i].distanceToMouse = sqrtf(static_cast<float>(
								pow(player->screen_pos.x - bulletA[i].mousePosX, 2) +
								pow(player->screen_pos.y - bulletA[i].mousePosY, 2)));
							bulletA[i].frontPos.x = player->screen_pos.x;
							bulletA[i].frontPos.y = player->screen_pos.y;
							bulletA[i].theta = acosf((-bulletA[i].mousePosX + bulletA[i].frontPos.x) / bulletA[i].distanceToMouse);
							break;
						}
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
					bulletA[i].gravitySpeedY += 2.0f;

					if (bulletA[i].frontPos.x - bulletA[i].mousePosX > 50.0f) {
						bulletA[i].theta -= (M_PI1 / 30.0f);
					}
					else if (bulletA[i].mousePosX - bulletA[i].frontPos.x > 50.0f) {
						bulletA[i].theta += (M_PI1 / 30.0f);
					}

					if (bulletA[i].screen_pos.y > 500.0f) {
						bulletA[i].isShoot = false;
					}
				}
				if (bulletA[i].pos.z > 1100.0f) {
					bulletA[i].isShoot = false;
				}

				bulletA[i].lastPos = getLastPos(bulletA[i].savePos.z, bulletA[i].speed, bulletA[i].distanceToMouse, bulletA[i].frontPos.x, bulletA[i].frontPos.y, bulletA[i].mousePosX, bulletA[i].mousePosY);
				bulletA[i].screen_pos.x = bulletA[i].newPos.x;
				bulletA[i].screen_pos.y = bulletA[i].newPos.y + bulletA[i].gravityY;
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
			Novice::DrawEllipse(static_cast<int>(bulletA[i].lastPos.x), static_cast<int>(bulletA[i].lastPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, WHITE, kFillModeWireFrame);
		}
	}
	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (bulletA[i].isShoot) {
			Novice::DrawEllipse(static_cast<int>(bulletA[i].screen_pos.x + 10.0f), static_cast<int>(bulletA[i].screen_pos.y), static_cast<int>(bulletA[i].radiusX * bulletA[i].scale), static_cast<int>(bulletA[i].radiusY * bulletA[i].scale), M_PI1 / 2 + bulletA[i].theta, 0x191B19FF, kFillModeSolid);
			Novice::DrawEllipse(static_cast<int>(bulletA[i].screen_pos.x - 10.0f), static_cast<int>(bulletA[i].screen_pos.y), static_cast<int>(bulletA[i].radiusX * bulletA[i].scale), static_cast<int>(bulletA[i].radiusY * bulletA[i].scale), M_PI1 / 2 + bulletA[i].theta, 0x191B19FF, kFillModeSolid);
			Novice::DrawEllipse(static_cast<int>(bulletA[i].screen_pos.x + 10.0f), static_cast<int>(bulletA[i].screen_pos.y), static_cast<int>(bulletA[i].radiusX * bulletA[i].scale), static_cast<int>(bulletA[i].radiusY * bulletA[i].scale), M_PI1 / 2 + bulletA[i].theta, 0x48e5c9FF, kFillModeWireFrame);
			Novice::DrawEllipse(static_cast<int>(bulletA[i].screen_pos.x - 10.0f), static_cast<int>(bulletA[i].screen_pos.y), static_cast<int>(bulletA[i].radiusX * bulletA[i].scale), static_cast<int>(bulletA[i].radiusY * bulletA[i].scale), M_PI1 / 2 + bulletA[i].theta, 0x48e5c9FF, kFillModeWireFrame);
		}
	}
}

/// <summary>
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

BulletB::BulletB() {
	for (int i = 0; i < MAX_BULLET_B; i++) {
		bulletB[i] = {
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		15.0f,	//radiusX
		15.0f,	//radiusY
		1.0f,	//scale 
		110.0f,	//speed
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
	for (int i = 0; i < MAX_BULLET_B; i++) {
		bulletB[i] = {
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//lastPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		15.0f,	//radiusX
		15.0f,	//radiusY
		1.0f,	//scale 
		110.0f,	//speed
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
				bulletB[i].frontPos.x += static_cast<int>(OUTER_BG_SPEED * (1100.0f - bulletB[i].pos.z) / 1100.0f);
			}
		}
		if (player->isPlayerRight) {
			if (keys[DIK_D]) {
				bulletB[i].mousePosX -= static_cast<int>(OUTER_BG_SPEED);
				bulletB[i].frontPos.x -= static_cast<int>(OUTER_BG_SPEED * (1100.0f - bulletB[i].pos.z) / 1100.0f);
			}
		}
	}
}

void BulletB::Shot(Player* player, Bullet* bullet) {
	if (player->isAlive) {
		if (player->shootCoolTimeB > 0) {
			player->shootCoolTimeB--;
		}
		else {
			player->isShootAbleB = true;
		}
		if (bullet->mouseType == false) {
			if (Novice::IsPressMouse(1)) {
				if (player->isShootAbleB) {
					player->isShootAbleB = false;
					player->shootCoolTimeB = 300;
					for (int i = 0; i < MAX_BULLET_B; i++) {
						if (!bulletB[i].isShoot) {
							bulletB[i].isShoot = true;
							bulletB[i].pos.x = player->pos.x;
							bulletB[i].pos.y = player->pos.y;
							bulletB[i].pos.z = player->pos.z;
							bulletB[i].randPos.x = (rand() % 101 - 50.0f);
							bulletB[i].randPos.y = (rand() % 80 + 1.0f);
							bulletB[i].randPos.z = (rand() % 101 + 1.0f);
							bulletB[i].time = 0.0f;
							bulletB[i].stoppageTimer = 0.0f;
							bulletB[i].stoppageTime = (70.0f + rand() % 31);
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
				}
				else {
					bulletB[i].pos.z += bulletB[i].speed + bulletB[i].randPos.z / 96.0f;
					bulletB[i].time += bulletB[i].speed / (bulletB[i].distanceToMouse * 3);
					if (bulletB[i].time > 1.05f) {
						bulletB[i].isShoot = false;
					}
				}
				bulletB[i].lastPos = { static_cast<float>(bulletB[i].mousePosX) , static_cast<float>(bulletB[i].mousePosY) };
				bulletB[i].screen_pos.x = bulletB[i].newPos.x;
				bulletB[i].screen_pos.y = bulletB[i].newPos.y;
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
			Novice::DrawEllipse(static_cast<int>(bulletB[i].lastPos.x), static_cast<int>(bulletB[i].lastPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, WHITE, kFillModeWireFrame);
		}
	}
	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (bulletB[i].isShoot) {
			Novice::DrawEllipse(static_cast<int>(bulletB[i].screen_pos.x), static_cast<int>(bulletB[i].screen_pos.y), static_cast<int>(bulletB[i].radiusX * bulletB[i].scale), static_cast<int>(bulletB[i].radiusY * bulletB[i].scale), 0.0f, 0x191B19FF, kFillModeSolid);
			Novice::DrawEllipse(static_cast<int>(bulletB[i].screen_pos.x), static_cast<int>(bulletB[i].screen_pos.y), static_cast<int>(bulletB[i].radiusX * bulletB[i].scale), static_cast<int>(bulletB[i].radiusY * bulletB[i].scale), 0.0f, 0x2ae690FF, kFillModeWireFrame);
		}
	}
}
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

BulletC::BulletC() {
	for (int i = 0; i < MAX_SHELL_C; i++) {
		for (int j = 0; j < MAX_BULLET_C; j++) {
			bulletC[i][j] = {
			{},		//pos
			{},		//randPos
			{},		//savePos
			{},		//newPos
			{},		//frontPos
			{},		//lastPos
			{},		//screen_pos
			0,		//mousePosX 
			0,		//mousePosY 
			0.0f,	//gravityY 
			0.0f,	//gravitySpeedY
			12.0f,	//radiusX
			12.0f,	//radiusY
			0.0f,	//theta
			1.0f,	//scale 
			25.0f,	//speed
			0.0f,	//time
			0.0f,	//distanceToMouse
			false	//isShoot 
			};
		}
	}
}

BulletC::~BulletC() {}

void BulletC::Init() {
	for (int i = 0; i < MAX_SHELL_C; i++) {
		for (int j = 0; j < MAX_BULLET_C; j++) {
			bulletC[i][j] = {
			{},		//pos
			{},		//randPos
			{},		//savePos
			{},		//newPos
			{},		//frontPos
			{},		//lastPos
			{},		//screen_pos
			0,		//mousePosX 
			0,		//mousePosY 
			0.0f,	//gravityY 
			0.0f,	//gravitySpeedY
			12.0f,	//radiusX
			12.0f,	//radiusY
			0.0f,	//theta
			1.0f,	//scale 
			25.0f,	//speed
			0.0f,	//time
			0.0f,	//distanceToMouse
			false	//isShoot 
			};
		}
	}
}

void BulletC::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_SHELL_C; i++) {
		for (int j = 0; j < MAX_BULLET_C; j++) {
			if (player->isPlayerLeft) {
				if (keys[DIK_A]) {
					bulletC[i][j].mousePosX += static_cast<int>(OUTER_BG_SPEED * (1100.0f - bulletC[i][j].pos.z) / 1100.0f);
				}
			}
			if (player->isPlayerRight) {
				if (keys[DIK_D]) {
					bulletC[i][j].mousePosX -= static_cast<int>(OUTER_BG_SPEED * (1100.0f - bulletC[i][j].pos.z) / 1100.0f);
				}
			}
		}
	}
}

void BulletC::Shot(Player* player, Bullet* bullet) {
	if (player->isAlive) {
		if (player->shootCoolTimeC > 0) {
			player->shootCoolTimeC--;
		}
		else {
			player->isShootAbleC = true;
		}
		if (bullet->mouseType) {
			if (Novice::IsPressMouse(0)) {
				if (player->isShootAbleC) {
					player->isShootAbleC = false;
					player->shootCoolTimeC = 60;
					for (int i = 0; i < MAX_SHELL_C; i++) {
						if (!bulletC[i][0].isShoot) {
							bulletC[i][0].isShoot = true;
							for (int j = 0; j < MAX_BULLET_C; j++) {
								bulletC[i][j].isShoot = true;
								bulletC[i][j].pos.z = player->pos.z;
								bulletC[i][j].randPos.x = (rand() % 51 - 25.0f);
								bulletC[i][j].randPos.y = (rand() % 51 - 25.0f);
								bulletC[i][j].savePos.z = player->pos.z;
								bulletC[i][j].time = 0.0f;
								bulletC[i][j].gravityY = 0.0f;
								bulletC[i][j].gravitySpeedY = 0.0f;
								Novice::GetMousePosition(&bulletC[i][j].mousePosX, &bulletC[i][j].mousePosY);
								bulletC[i][j].mousePosX += static_cast<int>(bulletC[i][j].randPos.x);
								bulletC[i][j].mousePosY += static_cast<int>(bulletC[i][j].randPos.y);
								bulletC[i][j].distanceToMouse = sqrtf(static_cast<float>(
									pow(player->screen_pos.x - bulletC[i][j].mousePosX, 2) +
									pow(player->screen_pos.y - bulletC[i][j].mousePosY, 2)));
								bulletC[i][j].frontPos.x = player->screen_pos.x;
								bulletC[i][j].frontPos.y = player->screen_pos.y;
								bulletC[i][j].theta = acosf((-bulletC[i][j].mousePosX + bulletC[i][j].frontPos.x) / bulletC[i][j].distanceToMouse);
							}
							break;
						}
					}
				}
			}
		}
		for (int i = 0; i < MAX_SHELL_C; i++) {
			if (bulletC[i][0].isShoot) {
				for (int j = 0; j < MAX_BULLET_C; j++) {
					bulletC[i][j].pos.z += bulletC[i][j].speed;
					bulletC[i][j].time += bulletC[i][j].speed / bulletC[i][j].distanceToMouse;
					bulletC[i][j].scale = 1.0f - bulletC[i][j].pos.z / 1500.0f;
					bulletC[i][j].newPos.x = (1 - bulletC[i][j].time) * bulletC[i][j].frontPos.x + bulletC[i][j].time * bulletC[i][j].mousePosX;
					bulletC[i][j].newPos.y = (1 - bulletC[i][j].time) * bulletC[i][j].frontPos.y + bulletC[i][j].time * bulletC[i][j].mousePosY;
					if (bulletC[i][j].time >= 1.0f) {
						bulletC[i][j].gravityY += bulletC[i][j].gravitySpeedY;
						bulletC[i][j].gravitySpeedY += 3.0f;

						if (bulletC[i][j].frontPos.x - bulletC[i][j].mousePosX > 50.0f) {
							bulletC[i][j].theta -= (M_PI1 / 30.0f);
						}
						else if (bulletC[i][j].mousePosX - bulletC[i][j].frontPos.x > 50.0f) {
							bulletC[i][j].theta += (M_PI1 / 30.0f);
						}
					}
					if (bulletC[i][j].pos.z > 700.0f) {
						bulletC[i][j].isShoot = false;
					}

					bulletC[i][j].lastPos = getLastPos(bulletC[i][j].savePos.z, bulletC[i][j].speed, bulletC[i][j].distanceToMouse, bulletC[i][j].frontPos.x, bulletC[i][j].frontPos.y, bulletC[i][j].mousePosX, bulletC[i][j].mousePosY);
					bulletC[i][j].screen_pos.x = bulletC[i][j].newPos.x;
					bulletC[i][j].screen_pos.y = bulletC[i][j].newPos.y + bulletC[i][j].gravityY;
				}
			}
			else {
				for (int j = 0; j < MAX_BULLET_C; j++) {
					bulletC[i][j].screen_pos = { NULL };
				}
			}
		}
	}
}

void BulletC::Draw() const {
	for (int i = 0; i < MAX_SHELL_C; i++) {
		if (bulletC[i][0].isShoot) {
			for (int j = 0; j < MAX_BULLET_C; j++) {
				Novice::DrawEllipse(static_cast<int>(bulletC[i][j].lastPos.x), static_cast<int>(bulletC[i][j].lastPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, WHITE, kFillModeWireFrame);
			}
		}
	}
	for (int i = 0; i < MAX_SHELL_C; i++) {
			for (int j = 0; j < MAX_BULLET_C; j++) {
				if (bulletC[i][j].isShoot) {
					if (bulletC[i][j].screen_pos.y <= 500.0f) {
						Novice::DrawEllipse(static_cast<int>(bulletC[i][j].screen_pos.x), static_cast<int>(bulletC[i][j].screen_pos.y), static_cast<int>(bulletC[i][j].radiusX * bulletC[i][j].scale), static_cast<int>(bulletC[i][j].radiusY * bulletC[i][j].scale), M_PI1 / 2 + bulletC[i][j].theta, 0x191B19FF, kFillModeSolid);
						Novice::DrawEllipse(static_cast<int>(bulletC[i][j].screen_pos.x), static_cast<int>(bulletC[i][j].screen_pos.y), static_cast<int>(bulletC[i][j].radiusX * bulletC[i][j].scale), static_cast<int>(bulletC[i][j].radiusY * bulletC[i][j].scale), M_PI1 / 2 + bulletC[i][j].theta, 0x65c5ddFF, kFillModeWireFrame);
					}
				}
			}
		
	}
}

///////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////

BulletD::BulletD() {
	pos = {};
	newPos = { -100.0f ,-100.0f };
	frontPos = {};
	lastPos = {};
	mousePosX = 0;
	mousePosY = 0;
	distanceToMouse = 0.0f;
	radiusX = 70.0f;
	radiusY = 70.0f;
	scale = 1.0f;
	speed = 10.0f;
	time = 0.0f;
	stoppageTime = 0.0f;
	stoppageTimer = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_D; i++) {
		bulletD[i] = {
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		15.0f,	//radiusX
		15.0f,	//radiusY
		1.0f,	//scale 
		0.02f,	//speed
		0,		//randTime
		0.0f,	//time
		false	//isShoot 
		};
	}
}

BulletD::~BulletD() {}

void BulletD::Init() {
	pos = {};
	newPos = { -100.0f ,-100.0f };
	frontPos = {};
	lastPos = {};
	mousePosX = 0;
	mousePosY = 0;
	distanceToMouse = 0.0f;
	radiusX = 70.0f;
	radiusY = 70.0f;
	scale = 1.0f;
	speed = 10.0f;
	time = 0.0f;
	stoppageTime = 0.0f;
	stoppageTimer = 0.0f;

	isShoot = false;

	screen_pos = {};

	for (int i = 0; i < MAX_BULLET_D; i++) {
		bulletD[i] = {
		{},		//pos
		{},		//randPos
		{},		//newPos
		{},		//frontPos
		{},		//screen_pos 
		0,		//mousePosX 
		0,		//mousePosY 
		15.0f,	//radiusX
		15.0f,	//radiusY
		1.0f,	//scale 
		0.02f,	//speed
		0,		//randTime
		0.0f,	//time
		false	//isShoot 
		};
	}
}

void BulletD::Scroll(Player* player, char keys[256]) {
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

void BulletD::Shot(Player* player, Bullet* bullet) {
	if (player->isAlive) {
		if (player->shootCoolTimeD > 0) {
			player->shootCoolTimeD--;
		}
		else {
			player->isShootAbleD = true;
		}
		if (bullet->mouseType) {
			if (Novice::IsPressMouse(1)) {
				if (player->isShootAbleD) {
					player->isShootAbleD = false;
					player->shootCoolTimeD = 360;
					if (!isShoot) {
						isShoot = true;
						pos.z = player->pos.z;
						stoppageTime = 180.0f;
						time = 0.0f;
						stoppageTimer = 0.0f;
						Novice::GetMousePosition(&mousePosX, &mousePosY);
						distanceToMouse = sqrtf(static_cast<float>(
							pow(player->screen_pos.x - mousePosX, 2) +
							pow(player->screen_pos.y - mousePosY, 2)));
					}
					for (int i = 0; i < MAX_BULLET_D; i++) {
						bulletD[i].randTime = (rand() % 70 + 1);
						bulletD[i].randPos.x = (rand() % 401 - 200.0f);
						bulletD[i].randPos.y = (rand() % 351 - 170.0f);
						bulletD[i].randPos.z = (rand() % 351 - 170.0f);
						bulletD[i].speed = ((rand() % 3 + 1) / 100.0f);
						bulletD[i].time = 0.0f;
						bulletD[i].frontPos.x = player->screen_pos.x + bulletD[i].randPos.x;
						bulletD[i].frontPos.y = player->screen_pos.y + bulletD[i].randPos.y;
						bulletD[i].pos.z = player->pos.z + bulletD[i].randPos.z;
					}

				}
			}
		}
		if (isShoot) {
			scale = 1.0f - pos.z / 2000.0f;
			stoppageTimer++;
			if (stoppageTimer <= stoppageTime) {
				frontPos.x = player->screen_pos.x;
				frontPos.y = player->screen_pos.y;
				for (int i = 0; i < MAX_BULLET_D; i++) {
					bulletD[i].randTime--;
					if (bulletD[i].randTime < 0) {
						bulletD[i].isShoot = true;
					}
					if (bulletD[i].isShoot) {
						bulletD[i].time += bulletD[i].speed;
						bulletD[i].newPos.x = (1 - bulletD[i].time) * bulletD[i].frontPos.x + bulletD[i].time * player->screen_pos.x;
						bulletD[i].newPos.y = (1 - bulletD[i].time) * bulletD[i].frontPos.y + bulletD[i].time * player->screen_pos.y;
						if (bulletD[i].time >= 1.0f) {
							bulletD[i].isShoot = false;
						}
					}
				}
			}
			else {
				pos.z += speed;
				newPos.x = (1 - time) * frontPos.x + time * mousePosX;
				newPos.y = (1 - time) * frontPos.y + time * mousePosY;
				time += 0.01f;
				if (time > 1.5f) {
					isShoot = false;
					newPos.x = -100.0f;
					newPos.y = -100.0f;
					for (int i = 0; i < MAX_BULLET_D; i++) {
						bulletD[i].isShoot = false;
					}
				}
			}
			lastPos = { static_cast<float>(mousePosX) , static_cast<float>(mousePosY) };
			screen_pos.x = newPos.x;
			screen_pos.y = newPos.y;
		}
		else {
			screen_pos = { NULL };
		}

	}
}

void BulletD::Draw() const {
	if (isShoot) {
		for (int i = 0; i < MAX_BULLET_D; i++) {
			if (bulletD[i].isShoot) {
				Novice::DrawEllipse(static_cast<int>(bulletD[i].newPos.x), static_cast<int>(bulletD[i].newPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, 0x191B19FF, kFillModeSolid);
				Novice::DrawEllipse(static_cast<int>(bulletD[i].newPos.x), static_cast<int>(bulletD[i].newPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, 0x6370f7FF, kFillModeWireFrame);
			}
		}
		Novice::DrawEllipse(static_cast<int>(lastPos.x), static_cast<int>(lastPos.y), static_cast<int>(5), static_cast<int>(5), 0.0f, WHITE, kFillModeWireFrame);
		Novice::DrawEllipse(static_cast<int>(screen_pos.x), static_cast<int>(screen_pos.y), static_cast<int>(radiusX * scale), static_cast<int>(radiusY * scale), 0.0f, 0x191B19FF, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(screen_pos.x), static_cast<int>(screen_pos.y), static_cast<int>(radiusX * scale), static_cast<int>(radiusY * scale), 0.0f, 0x6370f7FF, kFillModeWireFrame);
	}
}