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
FunnelBullet::~FunnelBullet() {
}

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
			//particle_generator.GenerateParticles(
			//	funnelBullet[i].pos.x,
			//	funnelBullet[i].pos.y
			//);

			float dx = funnelBullet[i].pos.x - funnelBullet[i].target_pos.x;
			float dy = funnelBullet[i].pos.y - funnelBullet[i].target_pos.y;
			if (sqrtf(dx * dx + dy * dy) < 32.0f) {
				//particle_generator.Destroy(
				//	funnelBullet[i].pos.x,
				//	funnelBullet[i].pos.y
				//);
				funnelBullet[i].isShoot = false;
			}
		}
	}

	//当たり判定
	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (funnelBullet[i].isShoot) {
			if (player->screen_pos.x + player->width / 2 >= funnelBullet[i].pos.x - funnelBullet[i].radius * funnelBullet[i].scale &&
				player->screen_pos.x - player->width / 2 <= funnelBullet[i].pos.x + funnelBullet[i].radius * funnelBullet[i].scale) {
				if (player->screen_pos.y + player->height / 2 >= funnelBullet[i].pos.y - funnelBullet[i].radius * funnelBullet[i].scale &&
					player->screen_pos.y - player->height / 2 <= funnelBullet[i].pos.y + funnelBullet[i].radius * funnelBullet[i].scale) {
					if (!player->isHit) {
						player->isHit = true;
						player->hp -= FUNNEL_ATK;
					}
					funnelBullet[i].isShoot = false;
				}
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


	//particle_generator.Render();


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
					0x191B19FF
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
					0x4BBC54FF,
					kFillModeSolid
				);
			}
		}
	}
}


DroneBullet::DroneBullet() {
	for (int i = 0; i < MAX_BULLET_DRONE; ++i) {
		droneBullets[i] = {
			{0.0f, 0.0f, 1.0f}, // pos
			{0.0f, 0.0f},       // velocity
			{0.0f, 0.0f},       // target_pos
			25.0f,              // radius
			1.0f,               // scale
			4.0f,               // speed
			0.0f,               // angle
			30.0f,
			100,                // cooldown
			false               // isShoot
		};
	}
}

DroneBullet::~DroneBullet() {
}

void DroneBullet::init() {
	for (int i = 0; i < MAX_BULLET_DRONE; ++i) {
		droneBullets[i] = {
			{0.0f, 0.0f, 1.0f}, // pos
			{0.0f, 0.0f},       // velocity
			{0.0f, 0.0f},       // target_pos
			25.0f,              // radius
			1.0f,               // scale
			4.0f,               // speed
			0.0f,               // angle
			30.0f,
			100,                // cooldown
			false               // isShoot
		};
	}
}

void DroneBullet::Shot(Player* player, Enemy* enemy) {

	for (int i = 0; i < MAX_BULLET_DRONE; ++i) {


		Vector3 dronePos;
		switch (i) {
		case 0:
			dronePos = { enemy->drone1.pos.x, enemy->drone1.pos.y, 1.0f };
			break;
		case 1:
			dronePos = { enemy->drone2.pos.x, enemy->drone2.pos.y,  1.0f };
			break;
		case 2:
			dronePos = { enemy->drone3.pos.x, enemy->drone3.pos.y,  1.0f };
			break;
		default:
			continue;
		}

		droneBullets[i].cooldown--;


		if (enemy->current_action == ActionID::Figure_Eight) {
			if (droneBullets[i].cooldown <= 0 && !droneBullets[i].isShoot) {
				droneBullets[i].cooldown = 150;


				droneBullets[i].pos.x = dronePos.x;
				droneBullets[i].pos.y = dronePos.y;
				droneBullets[i].pos.z = dronePos.z;


				droneBullets[i].target_pos.x = player->screen_pos.x;
				droneBullets[i].target_pos.y = player->screen_pos.y;

				float dirX = droneBullets[i].target_pos.x - droneBullets[i].pos.x;
				float dirY = droneBullets[i].target_pos.y - droneBullets[i].pos.y;
				float magnitude = sqrtf(dirX * dirX + dirY * dirY);

				droneBullets[i].velocity.x = (dirX / magnitude) * droneBullets[i].speed;
				droneBullets[i].velocity.y = (dirY / magnitude) * droneBullets[i].speed;

				droneBullets[i].isShoot = true;
			}
		}

		droneBullets[i].angle += 0.1f;
		if (droneBullets[i].angle >= 2 * static_cast<float>(M_PI)) {
			droneBullets[i].angle -= 2 * static_cast<float>(M_PI);
		}
	}


	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (droneBullets[i].isShoot) {

			droneBullets[i].pos.x += droneBullets[i].velocity.x;
			droneBullets[i].pos.y += droneBullets[i].velocity.y;

			float dirX = droneBullets[i].target_pos.x - droneBullets[i].pos.x;
			float dirY = droneBullets[i].target_pos.y - droneBullets[i].pos.y;
			float magnitude = sqrtf(dirX * dirX + dirY * dirY);

			droneBullets[i].time = magnitude / droneBullets[i].speed;
			droneBullets[i].velocity.x = dirX / droneBullets[i].time;
			droneBullets[i].velocity.y = dirY / droneBullets[i].time;

			droneBullets[i].pos.z = 1.0f - (droneBullets[i].pos.y - enemy->funnel[i].y) / (530.0f - enemy->funnel[i].y);
			droneBullets[i].pos.z = max(0.0f, droneBullets[i].pos.z);
			droneBullets[i].scale = 0.2f + 0.8f * (1.0f - droneBullets[i].pos.z);
			//particle_generator.GenerateParticles(
			//	droneBullets[i].pos.x,
			//	droneBullets[i].pos.y
			//);

			float dx = droneBullets[i].pos.x - droneBullets[i].target_pos.x;
			float dy = droneBullets[i].pos.y - droneBullets[i].target_pos.y;
			if (sqrtf(dx * dx + dy * dy) < 32.0f) {
				//particle_generator.Destroy(
				//	droneBullets[i].pos.x,
				//	droneBullets[i].pos.y
				//);
				droneBullets[i].isShoot = false;
			}
		}
	}

	//当たり判定
	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (droneBullets[i].isShoot) {
			if (player->screen_pos.x + player->width / 2 >= droneBullets[i].pos.x - droneBullets[i].radius * droneBullets[i].scale &&
				player->screen_pos.x - player->width / 2 <= droneBullets[i].pos.x + droneBullets[i].radius * droneBullets[i].scale) {
				if (player->screen_pos.y + player->height / 2 >= droneBullets[i].pos.y - droneBullets[i].radius * droneBullets[i].scale &&
					player->screen_pos.y - player->height / 2 <= droneBullets[i].pos.y + droneBullets[i].radius * droneBullets[i].scale) {
					if (!player->isHit) {
						player->isHit = true;
					}
					droneBullets[i].isShoot = false;
				}
			}
		}
	}
}

void DroneBullet::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_BULLET_DRONE; ++i) {
		if (droneBullets[i].isShoot) {
			float dx = droneBullets[i].pos.x - player->screen_pos.x;
			float dy = droneBullets[i].pos.y - player->screen_pos.y;
			float dz = droneBullets[i].pos.z;

			float theta = atan2(dy, dx);

			float scrollFactor = OUTER_BG_SPEED * dz * sin(theta);

			if (droneBullets[i].pos.y < 530.0f) {
				if (player->isPlayerLeft && keys[DIK_A]) {
					droneBullets[i].pos.x -= scrollFactor;
				}
				if (player->isPlayerRight && keys[DIK_D]) {
					droneBullets[i].pos.x += scrollFactor;
				}
			}
		}
	}
}

void DroneBullet::Draw() {

	//particle_generator.Render();

	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		float posX = droneBullets[i].pos.x; //現在のX座標
		float posY = droneBullets[i].pos.y; //現在のY座標
		float radius = droneBullets[i].radius * droneBullets[i].scale; //半径

		float angleOffset = droneBullets[i].angle; //角度オフセット

		float outerPoints[5][2]{}; //starの点

		//点を計算
		for (int j = 0; j < 5; ++j) {
			//点の計算
			float outerAngle = angleOffset + j * (2 * static_cast<float>(M_PI) / 5);
			outerPoints[j][0] = posX + cos(outerAngle) * radius;
			outerPoints[j][1] = posY + sin(outerAngle) * radius;
		}

		if (droneBullets[i].isShoot) {
			//外部線を描画
			for (int j = 0; j < 5; ++j) {
				int next = (j + 2) % 5; //次の点を選択

				//線を描画
				Novice::DrawLine(
					static_cast<int>(outerPoints[j][0]),
					static_cast<int>(outerPoints[j][1]),
					static_cast<int>(outerPoints[next][0]),
					static_cast<int>(outerPoints[next][1]),
					0x191B19FF
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
					0x4BBC54FF,
					kFillModeSolid
				);
			}
		}
	}
}