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
	pos.z = 1000.0f;
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


}
//デストラクタ
Enemy::~Enemy() {}


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
	pos.z = 1000.0f;
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
					color = BLACK;
				}
			}
		}
	}

	for (int i = 0; i < MAX_BULLET_B; i++) {
		if (pos.x + width / 2 >= bulletB->bulletB[i].screen_pos.x - bulletB->bulletB[i].radius / 2 &&
			pos.x - width / 2 <= bulletB->bulletB[i].screen_pos.x + bulletB->bulletB[i].radius / 2) {
			if (pos.y + height / 2 >= bulletB->bulletB[i].screen_pos.y - bulletB->bulletB[i].radius / 2 &&
				pos.y - height / 2 <= bulletB->bulletB[i].screen_pos.y + bulletB->bulletB[i].radius / 2) {
				color = BLACK;
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
	/*pos.x += 5;*/

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

}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////