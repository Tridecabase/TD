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
		0.0f,	//angle
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
		0.0f,	//angle
		0.0f,	//time
		120,	//cooldown
		0.0f,	//distanceToMouse
		0.0f,	//altitude
		0.0f,	//frontAltitude
		false	//isShoot 
		};
	}

}

void FunnelBullet::Shot(Player* player, Enemy* enemy) {
	//発射処理
	for (int i = 0; i < MAX_FUNNEL; i++) {
		//クールダウンタイマーのカウントダウン
		if (enemy->funnel[i].isActive) {
			funnelBullet[i].cooldown--;
		}

		//回転角度を更新
		funnelBullet[i].angle += 0.1f;
		if (funnelBullet[i].angle >= 2 * static_cast<float>(M_PI)) {
			funnelBullet[i].angle -= 2 * static_cast<float>(M_PI);
		}

		//発射条件が満たされた場合
		if (funnelBullet[i].cooldown <= 0) {
			//クールダウンをリセット
			funnelBullet[i].cooldown = 120;

			//弾の初期位置
			funnelBullet[i].pos.x = enemy->funnel[i].x;
			funnelBullet[i].pos.y = enemy->funnel[i].y;
			funnelBullet[i].pos.z = 1.0f;

			//発射時のプレイヤーの位置を記録
			funnelBullet[i].screen_pos.x = player->screen_pos.x;
			funnelBullet[i].screen_pos.y = player->screen_pos.y;

			//プレイヤーに向かう方向ベクトルを計算
			float dirX = funnelBullet[i].screen_pos.x - funnelBullet[i].pos.x;
			float dirY = funnelBullet[i].screen_pos.y - funnelBullet[i].pos.y;
			float magnitude = sqrtf(dirX * dirX + dirY * dirY);

			//方向ベクトルを正規化
			if (magnitude != 0.0f) {
				funnelBullet[i].speed = 5.0f;
				dirX /= magnitude;
				dirY /= magnitude;
				funnelBullet[i].gravityY = dirY * funnelBullet[i].speed;
				funnelBullet[i].gravitySpeedY = dirX * funnelBullet[i].speed;
			}

			funnelBullet[i].isShoot = true; // 発射フラグをオンに設定
		}
	}

	// 弾の移動処理
	for (int i = 0; i < MAX_FUNNEL; i++) {
		if (funnelBullet[i].isShoot) {
			//弾の位置を更新
			funnelBullet[i].pos.x += funnelBullet[i].gravitySpeedY; //X方向の移動
			funnelBullet[i].pos.y += funnelBullet[i].gravityY;      //Y方向の移動
			funnelBullet[i].pos.z -= BULLET_VEL_Z;                  //Z方向の減少

			//奥行きに応じてスケールを調整
			funnelBullet[i].scale = 1.0f - funnelBullet[i].pos.z;

			particle_generator.GenerateParticles(funnelBullet[i].pos.x, funnelBullet[i].pos.y);

			////弾がターゲット座標（screen_pos）に到達したかを判定
			//if ((funnelBullet[i].gravitySpeedY > 0 && funnelBullet[i].pos.x >= funnelBullet[i].screen_pos.x) ||
			//	(funnelBullet[i].gravitySpeedY < 0 && funnelBullet[i].pos.x <= funnelBullet[i].screen_pos.x)) {
			//	//X座標が一致した場合
			//	if ((funnelBullet[i].gravityY > 0 && funnelBullet[i].pos.y >= funnelBullet[i].screen_pos.y) ||
			//		(funnelBullet[i].gravityY < 0 && funnelBullet[i].pos.y <= funnelBullet[i].screen_pos.y)) {
			//		//Y座標が一致した場合
			//		funnelBullet[i].isShoot = false; //弾を消す
			//	}
			//}
		}
	}
}

void FunnelBullet::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		if (funnelBullet[i].isShoot) {

			if (player->isPlayerLeft && keys[DIK_A]) {

				float scrollFactor = OUTER_BG_SPEED * funnelBullet[i].pos.z;
				funnelBullet[i].pos.x -= scrollFactor;
				funnelBullet[i].screen_pos.x += OUTER_BG_SPEED;
			}
			if (player->isPlayerRight && keys[DIK_D]) {

				float scrollFactor = OUTER_BG_SPEED * funnelBullet[i].pos.z;
				funnelBullet[i].pos.x += scrollFactor;
				funnelBullet[i].screen_pos.x -= OUTER_BG_SPEED;
			}
		}
	}
}

//描画処理
void FunnelBullet::Draw() {

	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		if (funnelBullet[i].isShoot) {
			particle_generator.Render();
		}
	}

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
					0x00FF0088
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
					0x005243FF,
					kFillModeSolid
				);
			}
		}
	}
}
