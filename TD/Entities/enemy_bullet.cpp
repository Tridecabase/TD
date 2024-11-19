#include "enemy_bullet.h"

FunnelBullet::FunnelBullet() {

	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		funnelBullet[i] = {
		{},	//pos
		{0.0f,0.0f},		//pos
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		30.0f,	//radius 
		1.0f,	//scale 
		20.0f,	//speed
		0.0f,	//time
		120,	//cooldown
		0.0f,	//distanceToMouse
		0.0f,	//altitude
		0.0f,	//frontAltitude
		false	//isShoot 
		};
	}

}
FunnelBullet::~FunnelBullet() {}

void FunnelBullet::init() {

	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		funnelBullet[i] = {
		{0.0f,0.0f,1.0f},	//pos
		{0.0f,0.0f},		//pos
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		10.0f,	//radius 
		1.0f,	//scale 
		30.0f,	//speed
		0.0f,	//time
		120,	//cooldown
		0.0f,	//distanceToMouse
		0.0f,	//altitude
		0.0f,	//frontAltitude
		false	//isShoot 
		};
	}

}

void FunnelBullet::Shot(Enemy* enemy) {

	//発射処理
	for (int i = 0; i < MAX_FUNNEL; i++) {
		//カウントダウン
		if (enemy->funnel[i].isActive)
		{
			funnelBullet[i].cooldown--;
		}
		//発射
		if (funnelBullet[i].cooldown <= 0) {
			funnelBullet[i].cooldown = 120;
			funnelBullet[i].pos.x = enemy->funnel[i].x;
			funnelBullet[i].pos.y = enemy->funnel[i].y;
			funnelBullet[i].pos.z = 1.0f;
			funnelBullet[i].isShoot = true;
		}

	}

	//移動
	for (int i = 0; i < MAX_FUNNEL; i++) {
		if (funnelBullet[i].isShoot) {
			funnelBullet[i].distanceToPlayer = sqrtf(static_cast<float>(pow(enemy->funnel[i].x - funnelBullet[i].pos.x, 2) + pow(enemy->funnel[i].y - funnelBullet[i].pos.y, 2)));
			funnelBullet[i].pos.z -= BULLET_VEL_Z;
			funnelBullet[i].scale = 1.0f - funnelBullet[i].pos.z;
			//test移動
			funnelBullet[i].pos.y += 5.0f;
			if (funnelBullet[i].pos.y > 600.0f) {
				funnelBullet[i].isShoot = false;
			}

		}
	}
}

void FunnelBullet::Scroll(Player* player, char keys[256]) {
	if (player->isPlayerLeft) {
		if (keys[DIK_A]) {
			for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
				if (funnelBullet[i].isShoot) {
					//test
					funnelBullet[i].pos.x += OUTER_BG_SPEED * (1.0f -funnelBullet[i].pos.z);
				}
			}
		}
	}
	if (player->isPlayerRight) {
		if (keys[DIK_D]) {
			for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
				if (funnelBullet[i].isShoot) {
					//test
					funnelBullet[i].pos.x -= OUTER_BG_SPEED * (1.0f - funnelBullet[i].pos.z);
				}
			}
		}
	}
}


//描画処理
void FunnelBullet::Draw(){
	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		Novice::DrawEllipse(
			static_cast<int>(funnelBullet[i].pos.x),
			static_cast<int>(funnelBullet[i].pos.y),
			static_cast<int>(funnelBullet[i].radius * funnelBullet[i].scale),
			static_cast<int>(funnelBullet[i].radius * funnelBullet[i].scale),
			0.0f, RED, kFillModeSolid
		);
	}
}
