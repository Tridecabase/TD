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
	hp = 1000;
	//最大HP
	max_hp = 1000;

	//敵の位置ベクトル
	pos.x = 640.0f;
	pos.y = 100.0f;
	pos.z = 1200.0f;
	//敵の長さ
	width = 40.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
	//敵の色
	color = WHITE;
	//敵の生存フラグ
	isAlive = true;

	//現在の行動
	current_action = ActionID::IDLE;
	//行動の残り時間
	action_timer = 1200;
	//ブレイクゲージ
	break_meter = max_hp/2;
	//ブレイクゲージの最大値
	break_meter_max = max_hp / 2;
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

	wave1 = new WaveGenerator(static_cast<float>((WINDOW_WIDTH - max_hp) / 2), 30.0f, hp, max_hp, BASE_AMP, WAVE_LENGTH, WAVE_SPEED, 100, 0xffffffff);
	wave2 = new WaveGenerator(static_cast<float>((WINDOW_WIDTH - max_hp) / 2), 30.0f, hp, max_hp, BASE_AMP + 1, WAVE_LENGTH - 20, float(WAVE_SPEED * 0.8), 120, BASE_COLOR);
	wave3 = new WaveGenerator(static_cast<float>((WINDOW_WIDTH - max_hp) / 2), 30.0f, hp, max_hp, BASE_AMP + 2, WAVE_LENGTH - 40 , float(WAVE_SPEED * 0.6), 150, BASE_COLOR);

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
	hp = max_hp;
	//敵の位置ベクトル
	pos.x = 640.0f;
	pos.y = 100.0f;
	pos.z = 1200.0f;
	//敵の長さ
	width = 40.0f;
	//敵の深さ
	depth = 20.0f;
	//敵の高さ
	height = 80.0f;
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

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Move(BulletA* bulletA,BulletB* bulletB) {

	if (hp <= 0) {
		hp = 0;
	}

	// ============================
	// 当たり判定
	// ============================

	color = WHITE;
	
	
	if (pos.x + width / 2 >= bulletA->screen_pos.x - bulletA->width / 2 &&
		pos.x - width / 2 <= bulletA->screen_pos.x + bulletA->width / 2) {
		if (pos.y + height / 2 >= bulletA->screen_pos.y - bulletA->height / 2 &&
			pos.y - height / 2 <= bulletA->screen_pos.y + bulletA->height / 2) {
			if (pos.z + depth / 2 >= bulletA->pos.z - bulletA->depth / 2 &&
				pos.z - depth / 2 <= bulletA->pos.z + bulletA->depth / 2) {
				tmp = bulletA->pos.z;
				//hpとhpbarを減らす
				color = BLACK;
				TakeDamage(10);
				//wave1->color = 0xff000055;
				//wave2->color = 0xff000055;
				//wave3->color = 0xff000055;
			}
		}
	}

	if (pos.x + width / 2 >= bulletB->screen_pos.x - bulletB->width / 2 &&
		pos.x - width / 2 <= bulletB->screen_pos.x + bulletB->width / 2) {
		if (pos.y + height / 2 >= bulletB->screen_pos.y - bulletB->height / 2 &&
			pos.y - height / 2 <= bulletB->screen_pos.y + bulletB->height / 2) {
				//hpとhpbarを減らす
				color = BLACK;
				TakeDamage(10);
				//wave1->color = 0xff000055;
				//wave2->color = 0xff000055;
				//wave3->color = 0xff000055;
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
		break_timer--;
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
		PerformAction();
		action_timer--;
	}

	// ============================
	//	HP BARの更新処理
	// ============================

	wave1->total_length = hp;
	wave2->total_length = hp;
	wave3->total_length = hp;
	//wave1->color = 0xffffff55;
	//wave2->color = BASE_COLOR;
	//wave3->color = BASE_COLOR;
	wave1->numbers = static_cast<int>(hp / 2);
	wave2->numbers = static_cast<int>(hp / 2);
	wave3->numbers = static_cast<int>(hp / 2);

	wave1->WaveRandomUpdate();
	wave2->WaveRandomUpdate();
	wave3->WaveRandomUpdate();
}

//ダメージを受けた際の処理
void Enemy::TakeDamage(int damage) {
	hp -= damage;
	//ブレイクメーターはHPダメージの半分減少
	break_meter -= damage / 2;
	if (break_meter <= 0 && !is_break) {
		EnterBreakState();
	}
}

//ブレイクゲージを更新
void Enemy::UpdateBreakMeter() {
	if (!is_break && break_meter < break_meter_max) {
		//徐々にブレイクゲージを回復
		break_meter++; 
	}
}

//行動をランダムに選択して実行
void Enemy::PerformAction() {
	switch (current_action) {
	case ActionID::IDLE:

		break;
	case ActionID::MOVE_AND_DEPLOY:
		ExecuteMoveAndDeploy();
		break;
	case ActionID::FIRE_AT_PLAYER:
		ExecuteFireAtPlayer();
		break;
	case ActionID::BREAK_STATE:
		break; //ブレイク状態中は行動しない
	}
}

//行動を切り替え
void Enemy::SetRandomAction() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 1);

	int actionChoice = dist(gen);
	if (actionChoice == 0) {
		current_action = ActionID::MOVE_AND_DEPLOY;
		//行動の持続時間を設定
		action_timer = 1200;
	}
	else {
		current_action = ActionID::FIRE_AT_PLAYER;
		//行動持続時間
		action_timer = 1200;
	}
}

//行動ID 101
void Enemy::ExecuteMoveAndDeploy() {
	//pos.x += 5;

	//定期的に浮遊砲を設置
	//浮遊砲の間隔
	static int deploy_interval = 30;
	if (action_timer % deploy_interval == 0) {
		//発射した弾の関数
	}
}

//行動ID 102
void Enemy::ExecuteFireAtPlayer() const {
	//弾の発射間隔
	static int fire_interval = 20; 
	if (action_timer % fire_interval == 0) {
		//発射した弾の関数
	}
}

//ブレイク状態に入る
void Enemy::EnterBreakState() {
	is_break = true;
	//ブレイク状態の持続時間
	break_timer = 600;
	//ブレイクゲージをリセット
	break_meter = break_meter_max;
}

//ブレイク状態を終了
void Enemy::ExitBreakState() {
	is_break = false;
	//ブレイク終了後、行動を再設定
	SetRandomAction();
}

//プレイヤーの移動によってスクロール関数
void Enemy::Scroll(Player* player, char keys[256]) {
	if (player->isPlayerLeft) {
		if (keys[DIK_A]) {
			pos.x += OUTER_BG_SPEED;
		}
	}
	if (player->isPlayerRight) {
		if (keys[DIK_D]) {
			pos.x -= OUTER_BG_SPEED;
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

	//テスト：敵の描画
	Novice::DrawBox(
		static_cast<int>(screen_pos.x - width / 2),
		static_cast<int>(screen_pos.y - height / 2),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f, color, kFillModeSolid);

	Novice::ScreenPrintf(100, 140, "%f", tmp);
}

//logs
void Enemy::DrawInfo() {

	wave1->Render();
	wave2->Render();
	wave3->Render();

	Novice::DrawLine(
		static_cast<int>((WINDOW_WIDTH - max_hp) / 2),
		10,
		static_cast<int>((WINDOW_WIDTH - max_hp) / 2),
		50,
		0x00ff00ff
		);

	Novice::DrawLine(
		static_cast<int>((WINDOW_WIDTH - max_hp) / 2 + hp - 1),
		10,
		static_cast<int>((WINDOW_WIDTH - max_hp) / 2 + hp - 1),
		50,
		0x00ff00ff
	);

	Novice::DrawLine(
		static_cast<int>((WINDOW_WIDTH + max_hp) / 2 - 1),
		10,
		static_cast<int>((WINDOW_WIDTH + max_hp) / 2 - 1),
		50,
		0x00ff00ff
	);

}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////