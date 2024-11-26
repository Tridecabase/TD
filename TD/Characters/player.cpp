#include <Novice.h>
#include "player.h" 

// コンストラクタ
Player::Player() {
	// デフォルトの初期化
	Init(nullptr);
}

// デストラクタ
Player::~Player() {}


////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Player::Init(Map* map) {
	// blockSize のデフォルト値
	float blockSize = (map != nullptr) ? map->blockSize : 96.0f;

	// ============================
	// プレイヤ基本情報
	// ============================

	// プレイヤーの位置ベクトル
	pos.x = blockSize * 2.0f;
	pos.y = blockSize;
	pos.z = 50.0f;

	posNum = { 0.0f, 0.0f };
	tmpPos = { 0.0f, 0.0f };
	blockPos = { blockSize * 2.0f, blockSize };

	// プレイヤーの速度ベクトル
	speed = { blockSize, blockSize };

	// プレイヤーの長さと高さ
	width = 40.0f;
	height = 20.0f;

	// クールタイムと無敵時間
	moveCooltime = 0;
	graceTime = 60;

	// HP とステータス
	hp = PlAYER_MAX_HP;
	color1 = 0xf0de3dFF;
	isAlive = true;
	isHit = false;

	clock = 60;
	timer = 60;

	isPlayerLeft = false;
	isPlayerRight = false;

	//表示用
	mouseValue = 0;
	mouseType = false;

	// ============================
	// 弾丸関数変数
	// ============================
	shootCoolTimeA = 3;
	shootCoolTimeB = 300;
	shootCoolTimeC = 30;
	shootCoolTimeD = 360;

	isShootAbleA = false;
	isShootAbleB = false;
	isShootAbleC = false;
	isShootAbleD = false;

	// ============================
	// 背景用のメンバー変数を
	// ============================
	screen_pos = {};
}

void Player::InitDisplay() {
	Init(nullptr);
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Player::Move(Map* map, char keys[256], char preKeys[256]) {
	//=== 安全性チェック ===
	if (map == nullptr || keys == nullptr || preKeys == nullptr) {
		// 必要な引数が無効な場合、安全に終了
		return;
	}

	//=== 位置情報の計算 ===
	posNum.x = blockPos.x / speed.x;
	posNum.y = blockPos.y / speed.y;

	tmpPos.x = blockPos.x;
	tmpPos.y = blockPos.y;

	//アニメーション用タイマーを進める
	if (clock != timer) {
		clock++;
	}

	//=== プレイヤーの位置調整 ===
	if (posNum.y == 3) {
		pos.y = 52.0f;
		pos.z = 0.0f;
		width = 48.0f;
		height = 24.0f;

		if (posNum.x == 3) {
			pos.x = 120.0f;
		} else if (posNum.x == 2) {
			pos.x = 0.0f;
		} else if (posNum.x == 1) {
			pos.x = -120.0f;
		}
	} else if (posNum.y == 2) {
		pos.y = 0.0f;
		pos.z = 50.0f;
		width = 40.0f;
		height = 20.0f;

		if (posNum.x == 3) {
			pos.x = 106.0f;
		} else if (posNum.x == 2) {
			pos.x = 0.0f;
		} else if (posNum.x == 1) {
			pos.x = -107.0f;
		}
	} else if (posNum.y == 1) {
		pos.y = -46.0f;
		pos.z = 100.0f;
		width = 32.0f;
		height = 16.0f;

		if (posNum.x == 3) {
			pos.x = 91.0f;
		} else if (posNum.x == 2) {
			pos.x = 0.0f;
		} else if (posNum.x == 1) {
			pos.x = -93.0f;
		}
	}

	//=== プレイヤーの移動処理 ===
	if (!preKeys[DIK_W] && keys[DIK_W]) {
		tmpPos.y -= speed.y;
		posNum.y = tmpPos.y / speed.y;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			blockPos.y = tmpPos.y;
		}
		clock = 0;
		velocity = -1;
	}
	if (!preKeys[DIK_S] && keys[DIK_S]) {
		tmpPos.y += speed.y;
		posNum.y = tmpPos.y / speed.y;

		if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
			blockPos.y = tmpPos.y;
		}
		clock = 0;
		velocity = 1;
	}

	if (moveCooltime >= 0) {
		moveCooltime--;
	} else {
		moveCooltime = -1;

		if (keys[DIK_A]) {
			tmpPos.x -= speed.x;
			posNum.x = tmpPos.x / speed.x;

			if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
				blockPos.x = tmpPos.x;
				moveCooltime = 10;
			}
			clock = 0;
			velocity = -2;
		} else if (keys[DIK_D]) {
			tmpPos.x += speed.x;
			posNum.x = tmpPos.x / speed.x;

			if (map->block[(int)posNum.y][(int)posNum.x] == 0) {
				blockPos.x = tmpPos.x;
				moveCooltime = 10;
			}
			clock = 0;
			velocity = 2;
		}
	}

	//アニメーション終了時の速度リセット
	if (clock == timer) {
		velocity = 0;
	}

	//=== プレイヤーの画面上の位置を更新 ===
	screen_pos.x = map->blockPos.x + pos.x;
	screen_pos.y = map->blockPos.y + pos.y;

	//=== プレイヤーの状態確認 ===
	if (hp <= 0) {
		isAlive = false;
	}

	if (isAlive) {
		//プレイヤーがヒットした際の処理
		if (isHit) {
			if (graceTime > 0) {
				graceTime--;
			} else {
				graceTime = 60;
				isHit = false;
			}

			//無敵時間中の色変化
			if (graceTime % 4 == 2 || graceTime % 4 == 1) {
				color1 = 0x191B19FF; //ヒット時の色
			} else {
				if (mouseType) {
					color1 = 0x65c5ddFF; //通常時の色
				} else {
					color1 = 0x48e5c9FF;//通常時の色
				}
			}
		} else {
			if (mouseType) {
				color1 = 0x65c5ddFF; //通常時の色
			} else {
				color1 = 0x48e5c9FF;//通常時の色
			}
		}
	}

	//表示用
	mouseValue += static_cast<int>(fabs(Novice::GetWheel()));
	if (mouseValue > 550) {
		mouseValue = 0;
		if (mouseType) {
			mouseType = false;
		} else {
			mouseType = true;
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

float easyOut(int a, int b, float c, float t) {
	float time = c / t;
	float easedT = 1.0f - powf(1.0f - time, 3.0f);
	float x = (1.0f - easedT) * a + easedT * b;
	return x;
}

void Player::Draw(const int color, const bool Flat) const {
	int color2 = 0x191B19FF;
	int ballPrePosX = int(screen_pos.x);

	///翼の平常ポイント
	Vector2 point11N = { screen_pos.x - (width * 2.5f), screen_pos.y - (height * 6.0f) };
	Vector2 point12N = { screen_pos.x - (width * 1.4f), screen_pos.y - (height * 3.0f) };
	Vector2 point13N = { screen_pos.x - (width * 0.8f), screen_pos.y - (height * 4.3f) };
	Vector2 point14N = { screen_pos.x - (width * 0.5f), screen_pos.y - (height * 2.5f) };

	Vector2 point21N = { screen_pos.x + (width * 2.5f), screen_pos.y - (height * 6.0f) };
	Vector2 point22N = { screen_pos.x + (width * 1.4f), screen_pos.y - (height * 3.0f) };
	Vector2 point23N = { screen_pos.x + (width * 0.8f), screen_pos.y - (height * 4.3f) };
	Vector2 point24N = { screen_pos.x + (width * 0.5f), screen_pos.y - (height * 2.5f) };

	Vector2 point31N = { screen_pos.x - (width * 2.5f), screen_pos.y - (height * 0.8f) };
	Vector2 point32N = { screen_pos.x - (width * 1.0f), screen_pos.y - (height * 1.8f) };
	Vector2 point33N = { screen_pos.x - (width * 0.9f), screen_pos.y - (height * 0.9f) };
	Vector2 point34N = { screen_pos.x - (width * 0.5f), screen_pos.y - (height * 1.4f) };

	Vector2 point41N = { screen_pos.x + (width * 2.5f), screen_pos.y - (height * 0.8f) };
	Vector2 point42N = { screen_pos.x + (width * 1.0f), screen_pos.y - (height * 1.8f) };
	Vector2 point43N = { screen_pos.x + (width * 0.9f), screen_pos.y - (height * 0.9f) };
	Vector2 point44N = { screen_pos.x + (width * 0.5f), screen_pos.y - (height * 1.4f) };


	///プレイヤーが左へ移動する時、翼の位置
	Vector2 point11LP = { screen_pos.x - (width * 2.5f) + (width * 3.2f), screen_pos.y - (height * 6.0f) };
	Vector2 point12LP = { screen_pos.x - (width * 1.4f) + (width * 2.3f), screen_pos.y - (height * 3.0f) - (height * 1.0f) };
	Vector2 point13LP = { screen_pos.x - (width * 0.8f) + (width * 1.0f), screen_pos.y - (height * 4.3f) };
	Vector2 point14LP = { screen_pos.x - (width * 0.5f) + (width * 1.0f), screen_pos.y - (height * 2.5f) };

	Vector2 point21LP = { screen_pos.x + (width * 2.5f) + (width * 0.5f), screen_pos.y - (height * 6.0f) };
	Vector2 point22LP = { screen_pos.x + (width * 1.4f) + (width * 0.5f), screen_pos.y - (height * 3.0f) };
	Vector2 point23LP = { screen_pos.x + (width * 0.8f) + (width * 0.5f), screen_pos.y - (height * 4.3f) };
	Vector2 point24LP = { screen_pos.x + (width * 0.5f) + (width * 0.5f), screen_pos.y - (height * 2.5f) };

	Vector2 point31LP = { screen_pos.x - (width * 2.5f) + (width * 3.2f), screen_pos.y - (height * 0.8f) };
	Vector2 point32LP = { screen_pos.x - (width * 1.0f) + (width * 1.7f), screen_pos.y - (height * 1.8f) + (height * 0.3f) };
	Vector2 point33LP = { screen_pos.x - (width * 0.9f) + (width * 1.0f), screen_pos.y - (height * 0.9f) };
	Vector2 point34LP = { screen_pos.x - (width * 0.5f) + (width * 1.0f), screen_pos.y - (height * 1.4f) };

	Vector2 point41LP = { screen_pos.x + (width * 2.5f) + (width * 0.5f), screen_pos.y - (height * 0.8f) };
	Vector2 point42LP = { screen_pos.x + (width * 1.0f) + (width * 0.5f), screen_pos.y - (height * 1.8f) };
	Vector2 point43LP = { screen_pos.x + (width * 0.9f) + (width * 0.5f), screen_pos.y - (height * 0.9f) };
	Vector2 point44LP = { screen_pos.x + (width * 0.5f) + (width * 0.5f), screen_pos.y - (height * 1.4f) };

	///プレイヤーが右へ移動する時、翼の位置
	Vector2 point11RP = { screen_pos.x - (width * 2.5f) - (width * 0.5f), screen_pos.y - (height * 6.0f) };
	Vector2 point12RP = { screen_pos.x - (width * 1.4f) - (width * 0.5f), screen_pos.y - (height * 3.0f) };
	Vector2 point13RP = { screen_pos.x - (width * 0.8f) - (width * 0.5f), screen_pos.y - (height * 4.3f) };
	Vector2 point14RP = { screen_pos.x - (width * 0.5f) - (width * 0.5f), screen_pos.y - (height * 2.5f) };

	Vector2 point21RP = { screen_pos.x + (width * 2.5f) - (width * 3.2f), screen_pos.y - (height * 6.0f) };
	Vector2 point22RP = { screen_pos.x + (width * 1.4f) - (width * 2.3f), screen_pos.y - (height * 3.0f) - (height * 1.0f) };
	Vector2 point23RP = { screen_pos.x + (width * 0.8f) - (width * 1.0f), screen_pos.y - (height * 4.3f) };
	Vector2 point24RP = { screen_pos.x + (width * 0.5f) - (width * 1.0f), screen_pos.y - (height * 2.5f) };

	Vector2 point31RP = { screen_pos.x - (width * 2.5f) - (width * 0.5f), screen_pos.y - (height * 0.8f) };
	Vector2 point32RP = { screen_pos.x - (width * 1.0f) - (width * 0.5f), screen_pos.y - (height * 1.8f) };
	Vector2 point33RP = { screen_pos.x - (width * 0.9f) - (width * 0.5f), screen_pos.y - (height * 0.9f) };
	Vector2 point34RP = { screen_pos.x - (width * 0.5f) - (width * 0.5f), screen_pos.y - (height * 1.4f) };

	Vector2 point41RP = { screen_pos.x + (width * 2.5f) - (width * 3.2f), screen_pos.y - (height * 0.8f) };
	Vector2 point42RP = { screen_pos.x + (width * 1.0f) - (width * 1.7f), screen_pos.y - (height * 1.8f) + (height * 0.3f) };
	Vector2 point43RP = { screen_pos.x + (width * 0.9f) - (width * 1.0f), screen_pos.y - (height * 0.9f) };
	Vector2 point44RP = { screen_pos.x + (width * 0.5f) - (width * 1.0f), screen_pos.y - (height * 1.4f) };

	///翼今のポイント
	Vector2 point11 = { screen_pos.x - (width * 2.5f), screen_pos.y - (height * 6.0f) };
	Vector2 point12 = { screen_pos.x - (width * 1.4f), screen_pos.y - (height * 3.0f) };
	Vector2 point13 = { screen_pos.x - (width * 0.8f), screen_pos.y - (height * 4.3f) };
	Vector2 point14 = { screen_pos.x - (width * 0.5f), screen_pos.y - (height * 2.5f) };

	Vector2 point21 = { screen_pos.x + (width * 2.5f), screen_pos.y - (height * 6.0f) };
	Vector2 point22 = { screen_pos.x + (width * 1.4f), screen_pos.y - (height * 3.0f) };
	Vector2 point23 = { screen_pos.x + (width * 0.8f), screen_pos.y - (height * 4.3f) };
	Vector2 point24 = { screen_pos.x + (width * 0.5f), screen_pos.y - (height * 2.5f) };

	Vector2 point31 = { screen_pos.x - (width * 2.5f), screen_pos.y - (height * 0.8f) };
	Vector2 point32 = { screen_pos.x - (width * 1.0f), screen_pos.y - (height * 1.8f) };
	Vector2 point33 = { screen_pos.x - (width * 0.9f), screen_pos.y - (height * 0.9f) };
	Vector2 point34 = { screen_pos.x - (width * 0.5f), screen_pos.y - (height * 1.4f) };

	Vector2 point41 = { screen_pos.x + (width * 2.5f), screen_pos.y - (height * 0.8f) };
	Vector2 point42 = { screen_pos.x + (width * 1.0f), screen_pos.y - (height * 1.8f) };
	Vector2 point43 = { screen_pos.x + (width * 0.9f), screen_pos.y - (height * 0.9f) };
	Vector2 point44 = { screen_pos.x + (width * 0.5f), screen_pos.y - (height * 1.4f) };


	//向き処理
	if (velocity == 2) {
		ballPrePosX = int(easyOut(int(screen_pos.x - (screen_pos.x / 60)), int(screen_pos.x), float(clock), float(timer)));

		point11.x = easyOut(int(point11RP.x), int(point11N.x), float(clock), float(timer));
		point11.y = easyOut(int(point11RP.y), int(point11N.y), float(clock), float(timer));
		point12.x = easyOut(int(point12RP.x), int(point12N.x), float(clock), float(timer));
		point12.y = easyOut(int(point12RP.y), int(point12N.y), float(clock), float(timer));
		point13.x = easyOut(int(point13RP.x), int(point13N.x), float(clock), float(timer));
		point13.y = easyOut(int(point13RP.y), int(point13N.y), float(clock), float(timer));
		point14.x = easyOut(int(point14RP.x), int(point14N.x), float(clock), float(timer));
		point14.y = easyOut(int(point14RP.y), int(point14N.y), float(clock), float(timer));

		point21.x = easyOut(int(point21RP.x), int(point21N.x), float(clock), float(timer));
		point21.y = easyOut(int(point21RP.y), int(point21N.y), float(clock), float(timer));
		point22.x = easyOut(int(point22RP.x), int(point22N.x), float(clock), float(timer));
		point22.y = easyOut(int(point22RP.y), int(point22N.y), float(clock), float(timer));
		point23.x = easyOut(int(point23RP.x), int(point23N.x), float(clock), float(timer));
		point23.y = easyOut(int(point23RP.y), int(point23N.y), float(clock), float(timer));
		point24.x = easyOut(int(point24RP.x), int(point24N.x), float(clock), float(timer));
		point24.y = easyOut(int(point24RP.y), int(point24N.y), float(clock), float(timer));

		point31.x = easyOut(int(point31RP.x), int(point31N.x), float(clock), float(timer));
		point31.y = easyOut(int(point31RP.y), int(point31N.y), float(clock), float(timer));
		point32.x = easyOut(int(point32RP.x), int(point32N.x), float(clock), float(timer));
		point32.y = easyOut(int(point32RP.y), int(point32N.y), float(clock), float(timer));
		point33.x = easyOut(int(point33RP.x), int(point33N.x), float(clock), float(timer));
		point33.y = easyOut(int(point33RP.y), int(point33N.y), float(clock), float(timer));
		point34.x = easyOut(int(point34RP.x), int(point34N.x), float(clock), float(timer));
		point34.y = easyOut(int(point34RP.y), int(point34N.y), float(clock), float(timer));

		point41.x = easyOut(int(point41RP.x), int(point41N.x), float(clock), float(timer));
		point41.y = easyOut(int(point41RP.y), int(point41N.y), float(clock), float(timer));
		point42.x = easyOut(int(point42RP.x), int(point42N.x), float(clock), float(timer));
		point42.y = easyOut(int(point42RP.y), int(point42N.y), float(clock), float(timer));
		point43.x = easyOut(int(point43RP.x), int(point43N.x), float(clock), float(timer));
		point43.y = easyOut(int(point43RP.y), int(point43N.y), float(clock), float(timer));
		point44.x = easyOut(int(point44RP.x), int(point44N.x), float(clock), float(timer));
		point44.y = easyOut(int(point44RP.y), int(point44N.y), float(clock), float(timer));
	}
	if (velocity == -2) {
		ballPrePosX = int(easyOut(int(screen_pos.x + (screen_pos.x / 40)), int(screen_pos.x), float(clock), float(timer)));

		point11.x = easyOut(int(point11LP.x), int(point11N.x), float(clock), float(timer));
		point11.y = easyOut(int(point11LP.y), int(point11N.y), float(clock), float(timer));
		point12.x = easyOut(int(point12LP.x), int(point12N.x), float(clock), float(timer));
		point12.y = easyOut(int(point12LP.y), int(point12N.y), float(clock), float(timer));
		point13.x = easyOut(int(point13LP.x), int(point13N.x), float(clock), float(timer));
		point13.y = easyOut(int(point13LP.y), int(point13N.y), float(clock), float(timer));
		point14.x = easyOut(int(point14LP.x), int(point14N.x), float(clock), float(timer));
		point14.y = easyOut(int(point14LP.y), int(point14N.y), float(clock), float(timer));

		point21.x = easyOut(int(point21LP.x), int(point21N.x), float(clock), float(timer));
		point21.y = easyOut(int(point21LP.y), int(point21N.y), float(clock), float(timer));
		point22.x = easyOut(int(point22LP.x), int(point22N.x), float(clock), float(timer));
		point22.y = easyOut(int(point22LP.y), int(point22N.y), float(clock), float(timer));
		point23.x = easyOut(int(point23LP.x), int(point23N.x), float(clock), float(timer));
		point23.y = easyOut(int(point23LP.y), int(point23N.y), float(clock), float(timer));
		point24.x = easyOut(int(point24LP.x), int(point24N.x), float(clock), float(timer));
		point24.y = easyOut(int(point24LP.y), int(point24N.y), float(clock), float(timer));

		point31.x = easyOut(int(point31LP.x), int(point31N.x), float(clock), float(timer));
		point31.y = easyOut(int(point31LP.y), int(point31N.y), float(clock), float(timer));
		point32.x = easyOut(int(point32LP.x), int(point32N.x), float(clock), float(timer));
		point32.y = easyOut(int(point32LP.y), int(point32N.y), float(clock), float(timer));
		point33.x = easyOut(int(point33LP.x), int(point33N.x), float(clock), float(timer));
		point33.y = easyOut(int(point33LP.y), int(point33N.y), float(clock), float(timer));
		point34.x = easyOut(int(point34LP.x), int(point34N.x), float(clock), float(timer));
		point34.y = easyOut(int(point34LP.y), int(point34N.y), float(clock), float(timer));

		point41.x = easyOut(int(point41LP.x), int(point41N.x), float(clock), float(timer));
		point41.y = easyOut(int(point41LP.y), int(point41N.y), float(clock), float(timer));
		point42.x = easyOut(int(point42LP.x), int(point42N.x), float(clock), float(timer));
		point42.y = easyOut(int(point42LP.y), int(point42N.y), float(clock), float(timer));
		point43.x = easyOut(int(point43LP.x), int(point43N.x), float(clock), float(timer));
		point43.y = easyOut(int(point43LP.y), int(point43N.y), float(clock), float(timer));
		point44.x = easyOut(int(point44LP.x), int(point44N.x), float(clock), float(timer));
		point44.y = easyOut(int(point44LP.y), int(point44N.y), float(clock), float(timer));
	}


	float ballSize = width * 0.8f;
	float ballHeight = width;

	//テスト：プレイヤーの描画
	Novice::DrawEllipse(
		static_cast<int>(screen_pos.x),
		static_cast<int>(screen_pos.y),
		static_cast<int>(width),
		static_cast<int>(height),
		0.0f, color, kFillModeWireFrame);

	if (Flat) {
		Novice::DrawBox(static_cast<int>(screen_pos.x - width),
			static_cast<int>(screen_pos.y + height + 10),
			static_cast<int>(10 * width / 5), static_cast<int>(10.0f),
			0.0f, 0x191B19FF, kFillModeSolid);
		Novice::DrawBox(static_cast<int>(screen_pos.x - width),
			static_cast<int>(screen_pos.y + height + 10),
			static_cast<int>(hp * width / 5), static_cast<int>(10.0f),
			0.0f, 0x85f153FF, kFillModeSolid);
		Novice::DrawBox(static_cast<int>(screen_pos.x - width),
			static_cast<int>(screen_pos.y + height + 10),
			static_cast<int>(hp * width / 5), static_cast<int>(10.0f),
			0.0f, 0x191B19FF, kFillModeWireFrame);


		Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3),
			static_cast<int>(screen_pos.y - height + 10), static_cast<int>(10.0f),
			static_cast<int>(30 * height / 15),
			0.0f, 0x191B19FF, kFillModeSolid);
		Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3 + 10.0f),
			static_cast<int>(screen_pos.y + height + 10), static_cast<int>(10.0f),
			static_cast<int>(-480 * height / 390),
			0.0f, 0x191B19FF, kFillModeSolid);
		if (mouseType) {
			Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3),
				static_cast<int>(screen_pos.y + height + 10), static_cast<int>(10.0f),
				static_cast<int>(-((36 - shootCoolTimeD / 10) * height / 18)),
				0.0f, 0x6370f7FF, kFillModeSolid);
			Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3 + 10.0f),
				static_cast<int>(screen_pos.y + height + 10), static_cast<int>(10.0f),
				static_cast<int>(-(mouseValue)*height / 390),
				0.0f, 0x48e5c9FF, kFillModeSolid); 
		} else {
			Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3),
				static_cast<int>(screen_pos.y + height + 10), static_cast<int>(10.0f),
				static_cast<int>(-((30 - shootCoolTimeB / 10) * height / 15)),
				0.0f, 0x2ae690FF, kFillModeSolid);
			Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3 + 10.0f),
				static_cast<int>(screen_pos.y + height + 10), static_cast<int>(10.0f),
				static_cast<int>(-(mouseValue)*height / 390),
				0.0f, 0x65c5ddFF, kFillModeSolid);
		}
	}
	Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3),
		static_cast<int>(screen_pos.y - height + 10), static_cast<int>(10.0f),
		static_cast<int>(30 * height / 15),
		0.0f, 0x191B19FF, kFillModeWireFrame);
	Novice::DrawBox(static_cast<int>(screen_pos.x + width * 4 / 3 + 10.0f),
		static_cast<int>(screen_pos.y + height + 10), static_cast<int>(10.0f),
		static_cast<int>(-480 * height / 390),
		0.0f, 0x191B19FF, kFillModeWireFrame);

	Novice::DrawEllipse(
		static_cast<int>(screen_pos.x),
		static_cast<int>(screen_pos.y - ballHeight),
		static_cast<int>(ballSize),
		static_cast<int>(ballSize),
		0.0f, color2, kFillModeSolid);

	Novice::DrawEllipse(
		static_cast<int>(screen_pos.x),
		static_cast<int>(screen_pos.y - ballHeight),
		static_cast<int>(ballSize),
		static_cast<int>(ballSize),
		0.0f, color, kFillModeWireFrame);

	Novice::DrawEllipse(
		static_cast<int>(ballPrePosX),
		static_cast<int>(screen_pos.y - ballHeight),
		static_cast<int>(ballSize * 0.5f),
		static_cast<int>(ballSize * 0.5f),
		0.0f, color, kFillModeWireFrame);
	Novice::DrawEllipse(
		static_cast<int>(ballPrePosX),
		static_cast<int>(screen_pos.y - ballHeight),
		static_cast<int>(ballSize * 0.3f),
		static_cast<int>(ballSize * 0.3f),
		0.0f, color, kFillModeSolid);


	DrawPolygon(point11, point12, point14, point13, color2);
	Novice::DrawLine(int(point11.x), int(point11.y),
		int(point12.x), int(point12.y), color);
	Novice::DrawLine(int(point12.x), int(point12.y),
		int(point14.x), int(point14.y), color);
	Novice::DrawLine(int(point14.x), int(point14.y),
		int(point13.x), int(point13.y), color);
	Novice::DrawLine(int(point11.x), int(point11.y),
		int(point13.x), int(point13.y), color);

	DrawPolygon(point21, point22, point24, point23, color2);
	Novice::DrawLine(int(point21.x), int(point21.y),
		int(point22.x), int(point22.y), color);
	Novice::DrawLine(int(point22.x), int(point22.y),
		int(point24.x), int(point24.y), color);
	Novice::DrawLine(int(point24.x), int(point24.y),
		int(point23.x), int(point23.y), color);
	Novice::DrawLine(int(point21.x), int(point21.y),
		int(point23.x), int(point23.y), color);

	DrawPolygon(point31, point32, point34, point33, color2);
	Novice::DrawLine(int(point31.x), int(point31.y),
		int(point32.x), int(point32.y), color);
	Novice::DrawLine(int(point32.x), int(point32.y),
		int(point34.x), int(point34.y), color);
	Novice::DrawLine(int(point34.x), int(point34.y),
		int(point33.x), int(point33.y), color);
	Novice::DrawLine(int(point31.x), int(point31.y),
		int(point33.x), int(point33.y), color);

	DrawPolygon(point41, point42, point44, point43, color2);
	Novice::DrawLine(int(point41.x), int(point41.y),
		int(point42.x), int(point42.y), color);
	Novice::DrawLine(int(point42.x), int(point42.y),
		int(point44.x), int(point44.y), color);
	Novice::DrawLine(int(point44.x), int(point44.y),
		int(point43.x), int(point43.y), color);
	Novice::DrawLine(int(point41.x), int(point41.y),
		int(point43.x), int(point43.y), color);


	Novice::ScreenPrintf(10, 600, "%d", clock);
	Novice::ScreenPrintf(10, 620, "%d", timer);
	Novice::ScreenPrintf(10, 640, "%f", point11N);
	Novice::ScreenPrintf(10, 680, "%f", point11.x);
	Novice::ScreenPrintf(10, 660, "%f", point11LP.x);
}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////