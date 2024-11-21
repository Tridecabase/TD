#include "enemy_bullet.h"

FunnelBullet::FunnelBullet() {

	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		funnelBullet[i] = {
		{},	//pos
		{0.0f,0.0f},		//pos
		{0.0f,0.0f},		//target pos
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		30.0f,	//radius 
		1.0f,	//scale 
		3.0f,	//speed
		0.0f,	//angle
		150.0f,	//time
		100,	//cooldown
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
		{0.0f,0.0f},		//target pos
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		30.0f,	//radius 
		1.0f,	//scale 
		3.0f,	//speed
		0.0f,	//angle
		150.0f,	//time
		200,	//cooldown
		0.0f,	//distanceToMouse
		0.0f,	//altitude
		0.0f,	//frontAltitude
		false	//isShoot 
		};
	}

}

void FunnelBullet::Shot(Player* player, Enemy* enemy) {
	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (enemy->funnel[i].isActive) {
			funnelBullet[i].cooldown--;
		}


		funnelBullet[i].angle += 0.1f;
		if (funnelBullet[i].angle >= 2 * static_cast<float>(M_PI)) {
			funnelBullet[i].angle -= 2 * static_cast<float>(M_PI);
		}

		if (funnelBullet[i].cooldown <= 0 && !funnelBullet[i].isShoot) {
			funnelBullet[i].cooldown = 150;


			funnelBullet[i].pos.x = enemy->funnel[i].x;
			funnelBullet[i].pos.y = enemy->funnel[i].y;
			funnelBullet[i].pos.z = 1.0f;


			funnelBullet[i].target_pos.x = player->screen_pos.x;
			funnelBullet[i].target_pos.y = player->screen_pos.y;


			float dirX = funnelBullet[i].target_pos.x - funnelBullet[i].pos.x;
			float dirY = funnelBullet[i].target_pos.y - funnelBullet[i].pos.y;
			float magnitude = sqrtf(dirX * dirX + dirY * dirY);

			funnelBullet[i].time = magnitude / funnelBullet[i].speed;
			funnelBullet[i].velocity.x = dirX / funnelBullet[i].time;
			funnelBullet[i].velocity.y = dirY / funnelBullet[i].time;

			funnelBullet[i].isShoot = true;
		}
	}


	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (funnelBullet[i].isShoot) {

			funnelBullet[i].pos.x += funnelBullet[i].velocity.x;
			funnelBullet[i].pos.y += funnelBullet[i].velocity.y;

			float dirX = funnelBullet[i].target_pos.x - funnelBullet[i].pos.x;
			float dirY = funnelBullet[i].target_pos.y - funnelBullet[i].pos.y;
			float magnitude = sqrtf(dirX * dirX + dirY * dirY);

			funnelBullet[i].time = magnitude / funnelBullet[i].speed;
			funnelBullet[i].velocity.x = dirX / funnelBullet[i].time;
			funnelBullet[i].velocity.y = dirY / funnelBullet[i].time;

			funnelBullet[i].pos.z = 1.0f - (funnelBullet[i].pos.y - enemy->funnel[i].y) / (530.0f - enemy->funnel[i].y);
			funnelBullet[i].pos.z = max(0.0f, funnelBullet[i].pos.z);
			funnelBullet[i].scale = 0.2f + 0.8f * (1.0f - funnelBullet[i].pos.z);
			particle_generator.GenerateParticles(
				funnelBullet[i].pos.x,
				funnelBullet[i].pos.y
			);

			float dx = funnelBullet[i].pos.x - funnelBullet[i].target_pos.x;
			float dy = funnelBullet[i].pos.y - funnelBullet[i].target_pos.y;
			if (sqrtf(dx * dx + dy * dy) < 32.0f) {
				particle_generator.Destroy(
					funnelBullet[i].pos.x,
					funnelBullet[i].pos.y
				);
				funnelBullet[i].isShoot = false;
			}
		}
	}
}

void FunnelBullet::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		if (funnelBullet[i].isShoot) {

			float dx = funnelBullet[i].pos.x - player->screen_pos.x;
			float dy = funnelBullet[i].pos.y - player->screen_pos.y;
			float dz = funnelBullet[i].pos.z;

			float theta = atan2(dy, dx);

			float scrollFactor = OUTER_BG_SPEED * dz * sin(theta);

			if (funnelBullet[i].pos.y < 530.0f) {
				if (player->isPlayerLeft && keys[DIK_A]) {
					funnelBullet[i].pos.x -= scrollFactor;
				}
				if (player->isPlayerRight && keys[DIK_D]) {
					funnelBullet[i].pos.x += scrollFactor;
				}
			}
		}
	}
}

//描画処理
void FunnelBullet::Draw() {


	particle_generator.Render();


	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		float posX = funnelBullet[i].pos.x; //現在のX座標
		float posY = funnelBullet[i].pos.y; //現在のY座標
		float radius = funnelBullet[i].radius * funnelBullet[i].scale; //半径

		float angleOffset = funnelBullet[i].angle; //角度オフセット

		float outerPoints[5][2]{}; //starの点

		//点を計算
		for (int j = 0; j < 5; ++j) {
			//点の計算
			float outerAngle = angleOffset + j * (2 * static_cast<float>(M_PI) / 5);
			outerPoints[j][0] = posX + cos(outerAngle) * radius;
			outerPoints[j][1] = posY + sin(outerAngle) * radius;
		}

		if (funnelBullet[i].isShoot) {
			//外部線を描画
			for (int j = 0; j < 5; ++j) {
				int next = (j + 2) % 5; //次の点を選択

				//線を描画
				Novice::DrawLine(
					static_cast<int>(outerPoints[j][0]),
					static_cast<int>(outerPoints[j][1]),
					static_cast<int>(outerPoints[next][0]),
					static_cast<int>(outerPoints[next][1]),
					0x4BBC54FF
				);
			}

			//三角形を描画
			for (int j = 0; j < 5; ++j) {
				int next = (j + 2) % 5;

				Novice::DrawTriangle(
					static_cast<int>(outerPoints[j][0]),
					static_cast<int>(outerPoints[j][1]),
					static_cast<int>(outerPoints[next][0]),
					static_cast<int>(outerPoints[next][1]),
					static_cast<int>(posX),
					static_cast<int>(posY),
					0x191B19FF,
					kFillModeSolid
				);
			}
		}
	}
}
