#include <Novice.h>
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
	width = 60.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
	//敵の速度
	vel = 0.0f;
	//敵の色
	color = 0x191B19FF;
	//敵の生存フラグ
	isAlive = true;

	//現在の行動
	current_action = ActionID::IDLE;
	//行動の残り時間
	action_timer = 1200;
	//ブレイクゲージ
	break_meter = ENEMY_MAX_HP / 4;
	//ブレイクゲージの最大値
	break_meter_max = ENEMY_MAX_HP / 4;
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
		funnel[i].isHit = false;
		funnel[i].x = funnel[i].y = 0.0f;
		funnel[i].width = 64.0f;
		funnel[i].height = 64.0f;
		funnel[i].hp = 400;
		funnel[i].color = 0x005243FF;
		funnel[i].line_color = 0xB443ABFF;
		funnel[i].angle = 0x00FF0088;
		funnel[i].inner_center = { 0.0f ,0.0f };
		funnel[i].distance = { 0.0f ,0.0f };
		funnel[i].eyeball = { 0.0f ,0.0f };
		funnel[i].eyeball_r = funnel[i].width / 6;
		funnel[i].angleToPlayer = 0.0f;
	}

	center = {
	{640.0f,360.0f},		//位置
	{640.0f,360.0f},		//位置
	{5.0f,5.0f},			//半径
	0.0f,					//角度
	0XFF0000FF,				//色
	0.0f,					//運動傾斜角度
	0.0f,					//傾斜角度のラジアン
	0.0f,					//中心点の回転角度
	0.0f,					//回転カウンター
	{0.0f,20.0f},			//楕円の半径
	{0.0f,0.0f},			//速度
	0.5f,					//加速度
	};

	drone1 = {
		{0.0f,0.0f},			//位置
		{0.0f,0.0f},			//位置
		{32.0f,32.0f},			//半径
		0.0f,					//角度
		0x191B19FF,				//色
		30.0f,					//運動傾斜角度
		0.0f,					//傾斜角度のラジアン
		0.0f,					//中心点の回転角度
		0.0f,					//回転カウンター
		{150.0f,60.0f},			//楕円の半径
		{0.0f,0.0f},			//速度
		0.5f,					//加速度
	};

	drone2 = {
		{0.0f,0.0f},			//位置
		{0.0f,0.0f},			//位置
		{32.0f,32.0f},			//半径
		0.0f,					//角度
		0x191B19FF,				//色
		345.0f,					//運動傾斜角度
		0.0f,					//傾斜角度のラジアン
		10.0f,					//中心点の回転角度
		0.0f,					//回転カウンター
		{180.0f,110.0f},		//楕円の半径
		{0.0f,0.0f},			//速度
		0.5f,					//加速度
	};

	drone3 = {
		{0.0f,0.0f},			//位置
		{0.0f,0.0f},			//位置
		{32.0f,32.0f},			//半径
		0.0f,					//角度
		0x191B19FF,				//色
		0.0f,					//運動傾斜角度
		0.0f,					//傾斜角度のラジアン
		10.0f,					//中心点の回転角度
		0.0f,					//回転カウンター
		{0.0f,15.0f},			//楕円の半径
		{0.0f,0.0f},			//速度
		0.5f,					//加速度
	};

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
	width = 60.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
	//敵の速度
	vel = 0.0f;
	//敵の色
	color = 0x191B19FF;
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

	// 浮遊砲の初期化
	for (int i = 0; i < MAX_FUNNEL; ++i) {
		funnel[i].isActive = false;
		funnel[i].isHit = false;
		funnel[i].x = funnel[i].y = 0.0f;
		funnel[i].width = 64.0f;
		funnel[i].height = 64.0f;
		funnel[i].hp = 400;
		funnel[i].color = 0x005243FF;
		funnel[i].line_color = 0x4BBC54FF;
		funnel[i].angle = 0.0f;
		funnel[i].inner_center = { 0.0f ,0.0f };
		funnel[i].distance = { 0.0f ,0.0f };
		funnel[i].eyeball = { 0.0f ,0.0f };
		funnel[i].eyeball_r = funnel[i].width / 6;
		funnel[i].angleToPlayer = 0.0f;
	}

	center = {
	{640.0f,360.0f},		//位置
	{640.0f,360.0f},		//位置
	{5.0f,5.0f},			//半径
	0.0f,					//角度
	0XFF0000FF,				//色
	0.0f,					//運動傾斜角度
	0.0f,					//傾斜角度のラジアン
	0.0f,					//中心点の回転角度
	0.0f,					//回転カウンター
	{0.0f,20.0f},			//楕円の半径
	{0.0f,0.0f},			//速度
	0.5f,					//加速度
	};

	drone1 = {
		{0.0f,0.0f},			//位置
		{0.0f,0.0f},			//位置
		{32.0f,32.0f},			//半径
		0.0f,					//角度
		0x191B19FF,				//色
		30.0f,					//運動傾斜角度
		0.0f,					//傾斜角度のラジアン
		0.0f,					//中心点の回転角度
		0.0f,					//回転カウンター
		{150.0f,60.0f},			//楕円の半径
		{0.0f,0.0f},			//速度
		0.5f,					//加速度
	};

	drone2 = {
		{0.0f,0.0f},			//位置
		{0.0f,0.0f},			//位置
		{32.0f,32.0f},			//半径
		0.0f,					//角度
		0x191B19FF,				//色
		345.0f,					//運動傾斜角度
		0.0f,					//傾斜角度のラジアン
		10.0f,					//中心点の回転角度
		0.0f,					//回転カウンター
		{180.0f,110.0f},		//楕円の半径
		{0.0f,0.0f},			//速度
		0.5f,					//加速度
	};

	drone3 = {
		{0.0f,0.0f},			//位置
		{0.0f,0.0f},			//位置
		{32.0f,32.0f},			//半径
		0.0f,					//角度
		0x191B19FF,				//色
		0.0f,					//運動傾斜角度
		0.0f,					//傾斜角度のラジアン
		10.0f,					//中心点の回転角度
		0.0f,					//回転カウンター
		{0.0f,15.0f},			//楕円の半径
		{0.0f,0.0f},			//速度
		0.5f,					//加速度
	};

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Move(BulletA* bulletA, BulletB* bulletB) {


	// ============================
	// 敵描画関する計算
	// ============================

	//中心点の位置を記録
	center.pos.x = pos.x;
	center.pos.y = pos.y;

	drone3.tmp_pos.x = center.pos.x + 50.0f;
	drone3.tmp_pos.y = center.pos.y - 70.0f;

	if (current_action == ActionID::IDLE || current_action == ActionID::FIRE_AT_PLAYER) {
		drone1.tmp_pos.x = drone1.pos.x;
		drone1.tmp_pos.y = drone1.pos.y;
		drone2.tmp_pos.x = drone2.pos.x;
		drone2.tmp_pos.y = drone2.pos.y;

		//回転
		FloatingOver(drone1, center.pos.x, center.pos.y, 0.5f);
		FloatingOver(drone2, center.pos.x, center.pos.y, -1.2f);
		FloatingOver(drone3, center.pos.x + 50.0f, center.pos.y - 70.0f, 1.0f);
	}
	else if (current_action == ActionID::BREAK_STATE) {


	}
	else {
		//追跡
		drone1.pos = EaseOutBack(center.pos, drone1.pos, 1.0f);
		drone2.pos = EaseOutBack(center.pos , drone2.pos, 1.0f);
		drone3.pos = EaseOutBack(drone3.tmp_pos, drone3.pos, 1.0f);
	}


	// ============================
	// スクロールによってループ
	// ============================


	//敵位置をループさせる
	Loop(pos.x);
	Loop(drone1.pos.x);
	Loop(drone2.pos.x);
	Loop(drone3.pos.x);

	//浮遊砲をループさせる
	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (funnel[i].isActive) {
			Loop(funnel[i].x);
		}
	}


	// ============================
	// 敵HP
	// ============================

	//HPを0に超えないように
	if (hp <= 0) {
		hp = 0;
	}

	// ============================
	// 当たり判定
	// ============================

	color = 0x191B19FF;

	for (int i = 0; i < MAX_BULLET_A; i++) {
		if (bulletA->bulletA[i].isShoot) {
			if (pos.x + width / 2 >= bulletA->bulletA[i].screen_pos.x - bulletA->bulletA[i].radiusX / 2 &&
				pos.x - width / 2 <= bulletA->bulletA[i].screen_pos.x + bulletA->bulletA[i].radiusX / 2) {
				if (pos.y + height / 2 >= bulletA->bulletA[i].screen_pos.y - bulletA->bulletA[i].radiusY / 2 &&
					pos.y - height / 2 <= bulletA->bulletA[i].screen_pos.y + bulletA->bulletA[i].radiusY / 2) {
					if (pos.z + depth / 2 >= bulletA->bulletA[i].pos.z - bulletA->bulletA[i].radiusX / 2 &&
						pos.z - depth / 2 <= bulletA->bulletA[i].pos.z + bulletA->bulletA[i].radiusX / 2) {
						tmp = bulletA->bulletA[i].pos.z;
						color = RED;
						TakeDamage(PLAYER_ATK);
					}
				}
			}
		}
	}

	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (bulletB->bulletB[i].isShoot) {
			if (pos.x + width / 2 >= bulletB->bulletB[i].screen_pos.x - bulletB->bulletB[i].radiusX / 2 &&
				pos.x - width / 2 <= bulletB->bulletB[i].screen_pos.x + bulletB->bulletB[i].radiusX / 2) {
				if (pos.y + height / 2 >= bulletB->bulletB[i].screen_pos.y - bulletB->bulletB[i].radiusY / 2 &&
					pos.y - height / 2 <= bulletB->bulletB[i].screen_pos.y + bulletB->bulletB[i].radiusY / 2) {
					color = RED;
					TakeDamage(PLAYER_ATK);
				}
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
			break_meter = ENEMY_MAX_HP / 4;
			break_timer = 0;
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
		PerformAction();
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
	if (!is_break) {
	break_meter -= damage * 2;
	}
	if (break_meter <= 0 && !is_break) {
		EnterBreakState();
	}
}

//ブレイクゲージを更新
void Enemy::UpdateBreakMeter() const {
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
	const float maxSpeed = MAX_SPEED_;
	const float deployInterval = 1280.0f; //浮遊砲設置間隔
	static float distanceTraveled = 0.0f;

	if (action_timer >= 100) {
		//横の加速
		if (fabs(vel) < maxSpeed) {
			vel += (vel < 0 ? -0.2f : 0.2f);
		}

		pos.x += vel; // 位置更新

		//浮遊砲を設置
		distanceTraveled += fabs(vel);
		if (distanceTraveled >= deployInterval || distanceTraveled == 0.0f) {
			DeployFunnel(pos.x, pos.y); //浮遊砲を設置
			distanceTraveled = 0.0f;
		}
	}

	//巻き戻し処理
	if ((vel > 0 && pos.x >= WINDOW_WIDTH * MAX_SCROLL) || (vel < 0.0f && pos.x <= 0.0f)) {
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

//浮遊砲の更新処理
void Enemy::UpdateFunnel(Player* player, BulletA* bulletA, BulletB* bulletB) {

	// ============================
	// 動く
	// ============================

	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (funnel[i].isActive) {
			//浮動時間を増加
			funnel[i].floatTime += 0.01f; //浮動速度
			if (funnel[i].floatTime >= 2.0f * static_cast<float>(M_PI)) {
				funnel[i].floatTime -= 2.0f * static_cast<float>(M_PI);
			}

			//浮動オフセットの計算 (正弦波を利用)
			float floatOffset = sin(funnel[i].floatTime) * 0.3f; //浮動幅

			//外円の位置を更新
			float baseY = funnel[i].y; //外円の基準位置
			funnel[i].y = baseY + floatOffset;

			//内円の中心座標を計算
			funnel[i].inner_center.x = funnel[i].x + (funnel[i].width / 2 - funnel[i].width * 1 / 3) * cos(funnel[i].angle);
			funnel[i].inner_center.y = funnel[i].y + (funnel[i].height / 2 - funnel[i].height * 1 / 3) * sin(funnel[i].angle);

			//プレイヤーと内円の相対位置を計算
			funnel[i].distance.x = player->screen_pos.x - funnel[i].inner_center.x;
			funnel[i].distance.y = player->screen_pos.y - funnel[i].inner_center.y;

			//プレイヤーと内円の角度を計算
			funnel[i].angleToPlayer = atan2(funnel[i].distance.y, funnel[i].distance.x);

			//目の位置を計算
			float eyeballMaxOffset = funnel[i].width * 1 / 3 - funnel[i].eyeball_r; // 目が内円内に収まる最大距離
			funnel[i].eyeball.x = funnel[i].inner_center.x + eyeballMaxOffset * cos(funnel[i].angleToPlayer);
			funnel[i].eyeball.y = funnel[i].inner_center.y + eyeballMaxOffset * sin(funnel[i].angleToPlayer);

			// 内円の角度の更新
			funnel[i].angle += angular_speed;
			if (funnel[i].angle >= 2 * static_cast<float>(M_PI)) {
				funnel[i].angle -= 2 * static_cast<float>(M_PI);
			}
		}
	}


	// ============================
	// 当たり判定
	// ============================

	for (int i = 0; i < MAX_BULLET_A; i++) {
		for (int j = 0; j < MAX_FUNNEL; ++j) {
			if (funnel[j].x + funnel[j].width / 2 >= bulletA->bulletA[i].screen_pos.x - bulletA->bulletA[i].radiusX / 2 &&
				funnel[j].x - funnel[j].width / 2 <= bulletA->bulletA[i].screen_pos.x + bulletA->bulletA[i].radiusX / 2) {
				if (funnel[j].y + funnel[j].height / 2 >= bulletA->bulletA[i].screen_pos.y - bulletA->bulletA[i].radiusY / 2 &&
					funnel[j].y - funnel[j].height / 2 <= bulletA->bulletA[i].screen_pos.y + bulletA->bulletA[i].radiusY / 2) {
					if (pos.z + depth / 2 >= bulletA->bulletA[i].pos.z - bulletA->bulletA[i].radiusX / 2 &&
						pos.z - depth / 2 <= bulletA->bulletA[i].pos.z + bulletA->bulletA[i].radiusX / 2) {
						tmp = bulletA->bulletA[i].pos.z;
						funnel[j].isHit = true;
						funnel[j].hp -= PLAYER_ATK;
					}
				}
			}
		}
	}

	for (int i = 0; i < MAX_BULLET_B; i++) {
		for (int j = 0; j < MAX_FUNNEL; ++j) {
			if (funnel[j].x + funnel[j].width / 2 >= bulletB->bulletB[i].screen_pos.x - bulletB->bulletB[i].radiusX / 2 &&
				funnel[j].x - funnel[j].width / 2 <= bulletB->bulletB[i].screen_pos.x + bulletB->bulletB[i].radiusX / 2) {
				if (funnel[j].y + funnel[j].height / 2 >= bulletB->bulletB[i].screen_pos.y - bulletB->bulletB[i].radiusY / 2 &&
					funnel[j].y - funnel[j].height / 2 <= bulletB->bulletB[i].screen_pos.y + bulletB->bulletB[i].radiusY / 2) {
					if (pos.z + depth / 2 >= bulletB->bulletB[i].pos.z - bulletB->bulletB[i].radiusX / 2 &&
						pos.z - depth / 2 <= bulletB->bulletB[i].pos.z + bulletB->bulletB[i].radiusX / 2) {
						tmp = bulletB->bulletB[i].pos.z;
						funnel[j].isHit = true;
						funnel[j].hp -= PLAYER_ATK;

					}
				}
			}
		}
	}

	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (funnel[i].hp <= 0) {
			funnel[i].isActive = false; //浮游砲を無効化
		}

		if (funnel[i].isActive) {
			if (funnel[i].isHit) {
				funnel[i].color = 0xb7282eFF;
				funnel[i].line_color = 0x4BBC54FF;
				funnel[i].isHit = false;
			}
			else {
				funnel[i].color = 0x191B19FF;
				funnel[i].line_color = 0x4BBC54FF;
			}
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

	if (action_timer > 100) {
		angle += 0.05f;

		//移動
		float deltaX = cos(angle) * amplitudeX * 0.05f;		//横の変化量
		float deltaY = sin(2 * angle) * amplitudeY * 0.05f; //縦の変化量

		//現在位置を更新
		pos.x += speed + deltaX; //振動を追加
		pos.y += deltaY;         //縦方向の振動
	}
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
			drone1.pos.x += OUTER_BG_SPEED;
			drone2.pos.x += OUTER_BG_SPEED;
			drone3.pos.x += OUTER_BG_SPEED;
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
			drone1.pos.x -= OUTER_BG_SPEED;
			drone2.pos.x -= OUTER_BG_SPEED;
			drone3.pos.x -= OUTER_BG_SPEED;
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

	if (drone1.w >= static_cast<float>(M_PI)) {
		DrawRound(drone1, drone1.color);
		DrawCircle(drone1, 0x4BBC54FF);
	}
	if (drone2.w >= static_cast<float>(M_PI)) {
		DrawRound(drone2, drone2.color);
		DrawCircle(drone2, 0x4BBC54FF);
	}
	if (drone3.w >= static_cast<float>(M_PI)) {
		DrawRound(drone3, drone3.color);
		DrawCircle(drone3, 0x4BBC54FF);
	}

	//テスト：敵の描画
	Novice::DrawBox(
		static_cast<int>(screen_pos.x - width / 2),
		static_cast<int>(screen_pos.y - height / 2),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f, color, kFillModeSolid);
	Novice::DrawBox(
		static_cast<int>(screen_pos.x - width / 2),
		static_cast<int>(screen_pos.y - height / 2),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f, 0x4BBC54FF, kFillModeWireFrame);

	if (drone1.w < static_cast<float>(M_PI)) {
		DrawRound(drone1, drone1.color);
		DrawCircle(drone1, 0x4BBC54FF);
	}

	if (drone2.w < static_cast<float>(M_PI)) {
		DrawRound(drone2, drone2.color);
		DrawCircle(drone2, 0x4BBC54FF);
	}
	if (drone3.w < static_cast<float>(M_PI)) {
		DrawRound(drone3, drone3.color);
		DrawCircle(drone3, 0x4BBC54FF);
	}

	Novice::ScreenPrintf(100, 140, "%f", tmp);
}

void Enemy::DrawFunnel() const {

	for (int i = 0; i < MAX_FUNNEL; ++i) {
		if (funnel[i].isActive) {
			//外円の描画
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].x),
				static_cast<int>(funnel[i].y),
				static_cast<int>(funnel[i].width / 2),
				static_cast<int>(funnel[i].height / 2),
				0.0f,
				funnel[i].color,
				kFillModeSolid);


			//内円の陰影描画
			float t = 1.0f - float(pow(1.0f - funnel[i].angle / (2 * 3.14159265359f), 2));
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].x + (funnel[i].width / 2 - funnel[i].width * 4 / 9) * cos(funnel[i].angle + t * (2 * 3.14159265359f))),
				static_cast<int>(funnel[i].y + (funnel[i].height / 2 - funnel[i].height * 4 / 9) * sin(funnel[i].angle + t * (2 * 3.14159265359f))),
				static_cast<int>(funnel[i].width * 4 / 9),
				static_cast<int>(funnel[i].height * 4 / 9),
				0.0f,
				0x000b00FF,
				kFillModeSolid);

			//内円の陰影枠線描画
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].x + (funnel[i].width / 2 - funnel[i].width * 4 / 9) * cos(funnel[i].angle + t * (2 * 3.14159265359f))),
				static_cast<int>(funnel[i].y + (funnel[i].height / 2 - funnel[i].height * 4 / 9) * sin(funnel[i].angle + t * (2 * 3.14159265359f))),
				static_cast<int>(funnel[i].width * 4 / 9),
				static_cast<int>(funnel[i].height * 4 / 9),
				0.0f,
				funnel[i].line_color,
				kFillModeWireFrame);

			//外円の枠線描画
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].x),
				static_cast<int>(funnel[i].y),
				static_cast<int>(funnel[i].width / 2),
				static_cast<int>(funnel[i].height / 2),
				0.0f,
				funnel[i].line_color,
				kFillModeWireFrame);

			//内円の描画
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].x + (funnel[i].width / 2 - funnel[i].width * 1 / 3) * cos(funnel[i].angle)),
				static_cast<int>(funnel[i].y + (funnel[i].height / 2 - funnel[i].height * 1 / 3) * sin(funnel[i].angle)),
				static_cast<int>(funnel[i].width * 1 / 3),
				static_cast<int>(funnel[i].height * 1 / 3),
				0.0f,
				funnel[i].color,
				kFillModeSolid);

			//内円の枠線描画
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].x + (funnel[i].width / 2 - funnel[i].width * 1 / 3) * cos(funnel[i].angle)),
				static_cast<int>(funnel[i].y + (funnel[i].height / 2 - funnel[i].height * 1 / 3) * sin(funnel[i].angle)),
				static_cast<int>(funnel[i].width * 1 / 3),
				static_cast<int>(funnel[i].height * 1 / 3),
				0.0f,
				funnel[i].line_color,
				kFillModeWireFrame);

			//目の描画
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].eyeball.x),
				static_cast<int>(funnel[i].eyeball.y),
				static_cast<int>(funnel[i].eyeball_r),
				static_cast<int>(funnel[i].eyeball_r),
				0.0f,
				funnel[i].line_color,
				kFillModeSolid);

			//目の枠線描画
			Novice::DrawEllipse(
				static_cast<int>(funnel[i].eyeball.x),
				static_cast<int>(funnel[i].eyeball.y),
				static_cast<int>(funnel[i].eyeball_r),
				static_cast<int>(funnel[i].eyeball_r),
				0.0f,
				funnel[i].line_color,
				kFillModeWireFrame);
		}
	}
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
				10 - i,
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


/**
* フォロワーが中心点の動きにEaseOutBackの動きで追従する関数
*
* この関数は、フォロワーが中心点の動きにスムーズに追従し、特定の条件で
* 「回復運動（EaseOutBack）」を行うよう設計されています。
*
* 中心点が停止した場合、フォロワーは慣性で元のオフセット距離に戻ります。
* 中心点がランダムな方向に動く場合でも、フォロワーはその動きに対応します。
*
* 現在の中心点の位置（Vector2）
* フォロワーの現在の位置（Vector2）
* 緩和係数（0〜1の値でスムーズさを調整可能）
* @return 更新されたフォロワーの位置（Vector2）
*/
Vector2 Enemy::EaseOutBack(Vector2 centerPos, Vector2 followerPos, float easeAmount) {
	//中心点の前フレームの位置
	static Vector2 preCenterPos = { 0.0f, 0.0f };
	//フォロワーの速度
	static Vector2 velocity = { 0.0f, 0.0f };
	//相対位置
	static Vector2 initialOffset = { 10.0f, 10.0f };

	//中心点の前フレームから現在のフレームまでの移動量
	Vector2 centerDelta = Subtract(centerPos, preCenterPos);
	//フォロワー目標位置を計算
	Vector2 targetPosition = Add(preCenterPos, initialOffset);
	//フォロワーから目標位置への方向ベクトルを計算
	Vector2 toTarget = Subtract(targetPosition, followerPos);
	Vector2 direction = Normalize(toTarget);

	//加速によってフォロワーの速度を更新
	velocity.x += direction.x * ACCELERATION_ * easeAmount;
	velocity.y += direction.y * ACCELERATION_ * easeAmount;

	//速度を最大速度で制限
	float speed = Magnitude(velocity);
	if (speed > MAX_SPEED_) {
		velocity = Multiply(velocity, MAX_SPEED_ / speed);
	}

	//フォロワーの位置を更新
	followerPos = Add(followerPos, velocity);

	//中心点がほぼ停止している場合、フォロワーを初期オフセットに戻す
	if (Magnitude(centerDelta) < 0.01f) {
		Vector2 offset = Subtract(followerPos, centerPos);
		Vector2 restoreDirection = Normalize(Subtract(initialOffset, offset));
		Vector2 restoreForce = Multiply(restoreDirection, RESTORE_STRENGTH_ * easeAmount);
		followerPos = Add(followerPos, restoreForce);
	}

	//前フレームの中心点の位置を更新
	preCenterPos = centerPos;

	return followerPos;
}