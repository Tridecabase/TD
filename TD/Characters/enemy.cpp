﻿#include <Novice.h>
#include "enemy.h" 

//コンストラクタ
Enemy::Enemy() {

	// ============================
	// 敵基本情報
	// ============================

	//BOSSの名前
	name = "test=boss";
	//現在のHP
	hp = ENEMY_MAX_HP;

	//敵の位置ベクトル
	pos.x = 640.0f;
	pos.y = ENEMY_SPAWN_POSY;
	pos.z = 1090.0f;
	//敵の長さ
	width = 40.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
	//敵の速度
	vel = 0.0f;
	//敵の色
	color = WHITE;
	//敵の生存フラグ
	isAlive = true;

	//現在の行動
	current_action = ActionID::IDLE;
	//行動の残り時間
	action_timer = 1200;
	//ブレイクゲージ
	break_meter = ENEMY_MAX_HP / 2;
	//ブレイクゲージの最大値
	break_meter_max = ENEMY_MAX_HP / 2;
	//ブレイク状態フラグ
	is_break = false;
	//ブレイク状態の残り時間
	break_timer = 0;

	tmp = 0.0f;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTime = 10;
	//弾丸撃つのフラグ
	isShootAble = false;

	// ============================
	// 背景用のメンバー変数を
	// ============================

	screen_pos = {};

	// ============================
	//	HP BAR
	// ============================

	wave1 = new WaveGenerator(static_cast<float>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2), 30.0f, hp, ENEMY_MAX_HP, BASE_AMP, WAVE_LENGTH, WAVE_SPEED, 100, 0xffffffff);
	wave2 = new WaveGenerator(static_cast<float>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2), 30.0f, hp, ENEMY_MAX_HP, BASE_AMP + 1, WAVE_LENGTH - 20, float(WAVE_SPEED * 0.8), 120, BASE_COLOR);
	wave3 = new WaveGenerator(static_cast<float>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2), 30.0f, hp, ENEMY_MAX_HP, BASE_AMP + 2, WAVE_LENGTH - 40, float(WAVE_SPEED * 0.6), 150, BASE_COLOR);

	hpbar_r = 0x00;
	hpbar_g = 0xFF;
	hpbar_b = 0x00;
	hpbar_alpha = 0x00;


	// 浮遊砲の初期化
	for (int i = 0; i < MAX_FUNNEL; ++i) {
		funnel[i].isActive = false;
		funnel[i].x = funnel[i].y = 0.0f;
		funnel[i].width = 64.0f;
		funnel[i].height = 64.0f;
		funnel[i].hp = 0;
	}

}
//デストラクタ
Enemy::~Enemy() {
	delete wave1;
	delete wave2;
	delete wave3;
}


////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Init() {

	// ============================
	// 敵基本情報
	// ============================

	//敵のHP
	hp = ENEMY_MAX_HP;
	//敵の位置ベクトル
	pos.x = 640.0f;
	pos.y = ENEMY_SPAWN_POSY;
	pos.z = 1090.0f;
	//敵の長さ
	width = 40.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
	//敵の速度
	vel = 0.0f;
	//敵の色
	color = WHITE;
	//敵の生存フラグ
	isAlive = true;
	//敵のブレイクゲージ
	break_meter = break_meter_max;
	//敵のブレイク状態
	is_break = false;
	//敵のブレイク状態
	break_timer = 0;
	//SetRandomAction();

	tmp = 0.0f;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	shootCoolTime = 10;
	//弾丸撃つのフラグ
	isShootAble = false;

	hpbar_r = 0x00;
	hpbar_g = 0xFF;
	hpbar_b = 0x00;
	hpbar_alpha = 0x00;

	wave2->color = BASE_COLOR;
	wave3->color = BASE_COLOR;

	//浮遊砲の初期化
	for (int i = 0; i < MAX_FUNNEL; ++i) {
		funnel[i].isActive = false;
		funnel[i].x = funnel[i].y = 0.0f;
		funnel[i].width = 64.0f;
		funnel[i].height = 64.0f;
		funnel[i].hp = 0;
	}

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Move(BulletA* bulletA, BulletB* bulletB) {

	//HPを0に超えないように
	if (hp <= 0) {
		hp = 0;
	}

	//敵位置をループさせる
	if (pos.x < 0) {
		pos.x += WINDOW_WIDTH * 6;
	}
	if (pos.x >= WINDOW_WIDTH * 6) {
		pos.x -= WINDOW_WIDTH * 6;
	}

	//浮遊砲をループさせる
	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (funnel[i].isActive) {
			if (funnel[i].x < 0) {
				funnel[i].x += WINDOW_WIDTH * 6;
			}
			if (funnel[i].x >= WINDOW_WIDTH * 6) {
				funnel[i].x -= WINDOW_WIDTH * 6;
			}
		}
	}

	// ============================
	// 当たり判定
	// ============================

	color = WHITE;

	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (pos.x + width / 2 >= bulletA->bulletA[i].screen_pos.x - bulletA->bulletA[i].radius / 2 &&
			pos.x - width / 2 <= bulletA->bulletA[i].screen_pos.x + bulletA->bulletA[i].radius / 2) {
			if (pos.y + height / 2 >= bulletA->bulletA[i].screen_pos.y - bulletA->bulletA[i].radius / 2 &&
				pos.y - height / 2 <= bulletA->bulletA[i].screen_pos.y + bulletA->bulletA[i].radius / 2) {
				if (pos.z + depth / 2 >= bulletA->bulletA[i].pos.z - bulletA->bulletA[i].radius / 2 &&
					pos.z - depth / 2 <= bulletA->bulletA[i].pos.z + bulletA->bulletA[i].radius / 2) {
					tmp = bulletA->bulletA[i].pos.z;
					color = RED;
					bulletA[i].isShoot = false;
					TakeDamage(PLAYER_ATK);
				}
			}
		}
	}

	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (pos.x + width / 2 >= bulletB->bulletB[i].screen_pos.x - bulletB->bulletB[i].radius / 2 &&
			pos.x - width / 2 <= bulletB->bulletB[i].screen_pos.x + bulletB->bulletB[i].radius / 2) {
			if (pos.y + height / 2 >= bulletB->bulletB[i].screen_pos.y - bulletB->bulletB[i].radius / 2 &&
				pos.y - height / 2 <= bulletB->bulletB[i].screen_pos.y + bulletB->bulletB[i].radius / 2) {
				color = RED;
				bulletB[i].isShoot = false;
				TakeDamage(PLAYER_ATK);
			}
		}
	}


	screen_pos.x = pos.x;
	screen_pos.y = pos.y;

	// ============================
	// ブレイク判断
	// ============================

	// ブレイクゲージの回復
	UpdateBreakMeter();

	//ブレイク状態の場合、ブレイクタイマーを減らす
	if (is_break) {
		break_timer -= 2;
		if (break_timer <= 0) {
			ExitBreakState();
		}
	}
	else {

		// ============================
		//	敵の攻撃行動
		// ============================

		// 通常状態で行動モジュールを実行
		if (action_timer <= 0) {
			SetRandomAction();
		}
		/*PerformAction();*/
		action_timer--;
	}

	// ============================
	//	HP BARの更新処理
	// ============================

	wave1->total_length = hp;
	wave2->total_length = hp;
	wave3->total_length = hp;
	wave1->numbers = static_cast<int>(hp / 2);
	wave2->numbers = static_cast<int>(hp / 2);
	wave3->numbers = static_cast<int>(hp / 2);

	wave1->WaveRandomUpdate();
	wave2->WaveRandomUpdate();
	wave3->WaveRandomUpdate();

	if (hp < ENEMY_MAX_HP * 0.3) {
		wave2->color = 0xdc143cff;
		wave3->color = 0xdc143cff;
		hpbar_g = 0x00;
		hpbar_r = 0x0FF;
	}

	//浮遊砲の状態を更新
	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (funnel[i].isActive && funnel[i].hp <= 0) {
			//耐久値が0以下なら無効化
			funnel[i].isActive = false;
		}
	}
}

//ダメージを受けた際の処理
void Enemy::TakeDamage(int damage) {
	hp -= damage;
	//ブレイクメーターはHPダメージの半分減少
	break_meter -= damage * 2;
	if (break_meter <= 0 && !is_break) {
		EnterBreakState();
	}
}

//ブレイクゲージを更新
void Enemy::UpdateBreakMeter() {
	if (!is_break && break_meter < break_meter_max) {
		//徐々にブレイクゲージを回復
		//break_meter++; 
	}
}

//行動をランダムに選択して実行
void Enemy::PerformAction() {
	switch (current_action) {
	case ActionID::IDLE:
		Idle();
		break;
	case ActionID::MOVE_AND_DEPLOY:
		MoveAndDeploy();
		break;
	case ActionID::FIRE_AT_PLAYER:
		FireAtPlayer();
		break;
	case ActionID::Figure_Eight:
		FigureEight();
		break;
	case ActionID::BREAK_STATE:
		break;
	}
}

//行動を切り替え
void Enemy::SetRandomAction() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 3);

	int actionChoice = dist(gen);
	if (actionChoice == 1) {
		current_action = ActionID::MOVE_AND_DEPLOY;
		//行動の持続時間を設定
		action_timer = 600;
	}
	else if (actionChoice == 2) {
		current_action = ActionID::FIRE_AT_PLAYER;
		//行動の持続時間を設定
		action_timer = 600; // 行动持续时间
	}
	else if (actionChoice == 3) {
		current_action = ActionID::Figure_Eight;
		//行動の持続時間を設定
		action_timer = 300;
	}
}

void Enemy::MoveAndDeploy() {
	const float maxSpeed = 8.0f;
	const float deployInterval = 1280.0f; //浮遊砲設置間隔
	static float distanceTraveled = 0.0f;

	//横の加速
	if (fabs(vel) < maxSpeed) {
		vel += (vel < 0 ? -0.2f : 0.2f);
	}

	pos.x += vel; // 位置更新

	//浮遊砲を設置
	distanceTraveled += fabs(vel);
	if (distanceTraveled >= deployInterval) {
		DeployFunnel(pos.x, pos.y); //浮遊砲を設置
		distanceTraveled = 0.0f;
	}

	//巻き戻し処理
	if ((vel > 0 && pos.x >= WINDOW_WIDTH * 6) || (vel < 0.0f && pos.x <= 0.0f)) {
		//行動終了、リセット
		vel = 0.0f;
		current_action = ActionID::IDLE; //次はIDLEに遷移
		action_timer = 100;             //IDLEの時間設定
	}
}

// 浮遊砲の設置
void Enemy::DeployFunnel(float x, float y) {
	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (!funnel[i].isActive) {
			funnel[i].isActive = true;
			funnel[i].x = x;
			funnel[i].y = y;
			funnel[i].hp = 100;
			break;
		}
	}
}

//エネルギー収集と弾幕発射
void Enemy::FireAtPlayer() {
	static int chargeTime = 0;
	const int maxChargeTime = 300;

	chargeTime++;
	if (chargeTime >= maxChargeTime) {
		chargeTime = 0;
		current_action = ActionID::IDLE; //IDLEに遷移
		action_timer = 300;              //IDLE時間設定
	}
}


void Enemy::FigureEight() {
	const float speed = 4.0f;        //横の移動速度
	const float amplitudeX = 200.0f; //横の振幅
	const float amplitudeY = 150.0f; //縦の振幅
	static float angle = 0.0f;       //角度

	angle += 0.05f;

	//移動
	float deltaX = cos(angle) * amplitudeX * 0.05f;		//横の変化量
	float deltaY = sin(2 * angle) * amplitudeY * 0.05f; //縦の変化量

	//現在位置を更新
	pos.x += speed + deltaX; //振動を追加
	pos.y += deltaY;         //縦方向の振動
}


void Enemy::EnterBreakState() {
	is_break = true;
	break_timer = 600;
	break_meter = break_meter_max;
	current_action = ActionID::BREAK_STATE;
}

void Enemy::ExitBreakState() {
	is_break = false;
	action_timer = 0;
	SetRandomAction();
}

void Enemy::Idle() {
	// 高さをゆっくり元の位置へ戻す
	if (fabs(pos.y - ENEMY_SPAWN_POSY) > 1.0f) {
		pos.y += (ENEMY_SPAWN_POSY - pos.y) * 0.1f; // 緩やかな移動
	}
	else {
		SetRandomAction(); // ランダムな次の行動を選択
	}
}

//プレイヤーの移動によってスクロール関数
void Enemy::Scroll(Player* player, char keys[256]) {
	if (player->isPlayerLeft) {
		if (keys[DIK_A]) {
			pos.x += OUTER_BG_SPEED;
			for (int i = 0; i < MAX_FUNNEL; ++i) {
				if (funnel[i].isActive) {
					funnel[i].x += OUTER_BG_SPEED;
				}
			}
		}
	}
	if (player->isPlayerRight) {
		if (keys[DIK_D]) {
			pos.x -= OUTER_BG_SPEED;
			for (int i = 0; i < MAX_FUNNEL; ++i) {
				if (funnel[i].isActive) {
					funnel[i].x -= OUTER_BG_SPEED;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Draw() {

	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (funnel[i].isActive) {
			Novice::DrawBox(
				static_cast<int>(funnel[i].x - funnel[i].width / 2),
				static_cast<int>(funnel[i].y - funnel[i].height / 2),
				static_cast<int>(funnel[i].width),
				static_cast<int>(funnel[i].height),
				0.0f, 0x00FF00FF, kFillModeSolid);
		}
	}

	//テスト：敵の描画
	Novice::DrawBox(
		static_cast<int>(screen_pos.x - width / 2),
		static_cast<int>(screen_pos.y - height / 2),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f, color, kFillModeSolid);

	Novice::ScreenPrintf(100, 140, "%f", tmp);

	int centerX = int(pos.x);
	int centerY = int(pos.y);

	Novice::DrawLine(centerX - 15, centerY - 50, centerX - 30, centerY, GREEN);
	Novice::DrawLine(centerX - 30, centerY, centerX - 20, centerY + 50, GREEN);
	Novice::DrawLine(centerX - 20, centerY + 50, centerX + 20, centerY + 50, GREEN);
	Novice::DrawLine(centerX + 20, centerY + 50, centerX + 30, centerY, GREEN);
	Novice::DrawLine(centerX + 30, centerY, centerX + 15, centerY - 50, GREEN);
	Novice::DrawLine(centerX + 15, centerY - 50, centerX - 15, centerY - 50, GREEN);

	Novice::DrawLine(centerX, centerY - 30, centerX - 15, centerY + 30, GREEN);
	Novice::DrawLine(centerX - 15, centerY + 30, centerX + 15, centerY + 30, GREEN);
	Novice::DrawLine(centerX + 15, centerY + 30, centerX, centerY - 30, GREEN);

	Novice::DrawEllipse(centerX, centerY, 7, 7, 0.0f, GREEN, kFillModeWireFrame);

	Novice::DrawBox(centerX - 5, centerY - 45, 10, 7, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(centerX - 15, centerY + 5, 7, 7, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(centerX + 7, centerY + 5, 7, 7, 0.0f, GREEN, kFillModeWireFrame);

	Novice::DrawBox(centerX - 5, centerY + 50, 7, 12, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(centerX - 12, centerY + 65, 5, 7, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(centerX - 20, centerY + 75, 5, 5, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(centerX + 7, centerY + 65, 5, 7, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(centerX + 15, centerY + 75, 5, 5, 0.0f, GREEN, kFillModeWireFrame);

}

//HP BAR 描画
void Enemy::DrawInfo() {

	//HPbar　エフェクト
	for (int i = 0; i < 3; i++) {
		Novice::DrawBox(
			static_cast<int>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2),
			18 + i,
			ENEMY_MAX_HP,
			24 - i * 2,
			0.0f,
			(hpbar_r << 24) | (hpbar_g << 16) | (hpbar_b << 8) | (hpbar_alpha + i), kFillModeSolid
		);
	}

	for (int i = 0; i < 10; i++) {
		Novice::DrawBox(
			static_cast<int>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2),
			18 + i,
			hp,
			24 - i * 2,
			0.0f,
			(hpbar_r << 24) | (hpbar_g << 16) | (hpbar_b << 8) | (hpbar_alpha + i), kFillModeSolid
		);
	}

	//なみ
	wave1->Render();
	wave2->Render();
	wave3->Render();

	//左の線
	Novice::DrawLine(
		static_cast<int>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2),
		15,
		static_cast<int>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2),
		45,
		(hpbar_r << 24) | (hpbar_g << 16) | (hpbar_b << 8) | 0xFF
	);

	//右の線
	Novice::DrawLine(
		static_cast<int>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2 + hp - 1),
		15,
		static_cast<int>((WINDOW_WIDTH - ENEMY_MAX_HP) / 2 + hp - 1),
		45,
		(hpbar_r << 24) | (hpbar_g << 16) | (hpbar_b << 8) | 0xFF
	);

	//現在のHP
	Novice::DrawLine(
		static_cast<int>((WINDOW_WIDTH + ENEMY_MAX_HP) / 2 - 1),
		15,
		static_cast<int>((WINDOW_WIDTH + ENEMY_MAX_HP) / 2 - 1),
		45,
		(hpbar_r << 24) | (hpbar_g << 16) | (hpbar_b << 8) | 0xFF
	);

	// --- BREAK槽 ---
	if (break_timer > 0) {
		for (int i = 0; i < 10; i++) {
			Novice::DrawBox(
				(WINDOW_WIDTH / 2) - static_cast<int>(150.0f * break_timer / 600.0f),
				60 - i,
				static_cast<int>(300.0f * break_timer / 600.0f),
				20 - i * 2,
				0.0f,
				(0xCC << 24) | (0xCC << 16) | (0xCC << 8) | (255 - i * 25),
				kFillModeSolid
			);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////