#include "background.h"
#include <memory>

PlayerRoad::PlayerRoad() {
	{
		///横線用
		float y1 = 530.0f;
		float y2 = 572.0f;
		float y3 = 620.0f;
		float y4 = 682.0f;

		///縦線用
		float a1 = 45.0f;
		float a2 = 130.0f;
		float b1 = 63.0f;
		float b2 = 195.0f;

		///横線
		Line1P1 = { -1.0f, y1 };
		Line1P2 = { 1281.0f, y1 };
		Line2P1 = { -1.0f, y2 };
		Line2P2 = { 1281.0f, y2 };
		Line3P1 = { -1.0f, y3 };
		Line3P2 = { 1281.0f, y3 };
		Line4P1 = { -1.0f, y4 };
		Line4P2 = { 1281.0f, y4 };
		///縦線
		Line5P1 = { 640.0f - a2, y1 };
		Line5P2 = { 640.0f - b2, y4 };
		Line6P1 = { 640.0f - a1, y1 };
		Line6P2 = { 640.0f - b1, y4 };
		Line7P1 = { 640.0f + a1, y1 };
		Line7P2 = { 640.0f + b1, y4 };
		Line8P1 = { 640.0f + a2, y1 };
		Line8P2 = { 640.0f + b2, y4 };

		///矢印
		float c1 = 200.0f;
		float c2 = 170.0f;
		float d1 = 280.0f;
		float d2 = 250.0f;
		float e1 = 270.0f;
		float e2 = 240.0f;

		///左
		ArrowLeftPoint1 = { 640.0f - c1, y1 };
		ArrowLeftPoint2 = { 640.0f - c2, y1 };
		ArrowLeftPoint3 = { 640.0f - d1, 595.0f };
		ArrowLeftPoint4 = { 640.0f - d2, 595.0f };
		ArrowLeftPoint5 = { 640.0f - e1, y4 };
		ArrowLeftPoint6 = { 640.0f - e2, y4 };

		///右
		ArrowRightPoint1 = { 640.0f + c1, y1 };
		ArrowRightPoint2 = { 640.0f + c2, y1 };
		ArrowRightPoint3 = { 640.0f + d1, 595.0f };
		ArrowRightPoint4 = { 640.0f + d2, 595.0f };
		ArrowRightPoint5 = { 640.0f + e1, y4 };
		ArrowRightPoint6 = { 640.0f + e2, y4 };
	}

};

void PlayerRoad::render(Player* player, int color) const {

	if (player == nullptr) {
		return;
	}

	///横線
	Novice::DrawLine(int(Line1P1.x), int(Line1P1.y), int(Line1P2.x), int(Line1P2.y), color);
	//Novice::DrawLine(int(Line2P1.x), int(Line2P1.y), int(Line2P2.x), int(Line2P2.y), color);
	//Novice::DrawLine(int(Line3P1.x), int(Line3P1.y), int(Line3P2.x), int(Line3P2.y), color);
	//Novice::DrawLine(int(Line4P1.x), int(Line4P1.y), int(Line4P2.x), int(Line4P2.y), color);
	DrawLineNew(Line2P1, Line2P2, 3, color);
	DrawLineNew(Line3P1, Line3P2, 5, color);
	DrawLineNew(Line4P1, Line4P2, 7, color);

	///縦線
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x + 1), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x - 1), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x + 2), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x - 2), int(Line5P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x + 1), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x - 1), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x + 2), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x - 2), int(Line6P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x + 1), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x - 1), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x + 2), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x - 2), int(Line7P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x + 1), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x - 1), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x + 2), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x - 2), int(Line8P2.y), color);


	///矢印(左)
	if (player->isPlayerLeft) {
		DrawPolygon(ArrowLeftPoint1, ArrowLeftPoint2, ArrowLeftPoint3, ArrowLeftPoint4, ArrowLeftPoint5, ArrowLeftPoint6, color);
	}
	Novice::DrawLine(int(ArrowLeftPoint1.x), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x + 1), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x + 1), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x + 1), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x + 1), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x + 1), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x + 1), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x + 1), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x + 1), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x + 1), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x + 1), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x + 1), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x + 1), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x + 2), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x + 2), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x + 2), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x + 2), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x + 2), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x + 2), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x + 2), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x + 2), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x + 2), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x + 2), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x + 2), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x + 2), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x - 1), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x - 1), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x - 1), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x - 1), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x - 1), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x - 1), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x - 1), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x - 1), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x - 1), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x - 1), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x - 1), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x - 1), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x - 2), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x - 2), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x - 2), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x - 2), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x - 2), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x - 2), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x - 2), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x - 2), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x - 2), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x - 2), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x - 2), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x - 2), int(ArrowLeftPoint1.y), color);


	///矢印(左)
	if (player->isPlayerRight) {
		DrawPolygon(ArrowRightPoint1, ArrowRightPoint2, ArrowRightPoint3, ArrowRightPoint4, ArrowRightPoint5, ArrowRightPoint6, color);
	}
	Novice::DrawLine(int(ArrowRightPoint1.x), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x + 1), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x + 1), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x + 1), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x + 1), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x + 1), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x + 1), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x + 1), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x + 1), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x + 1), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x + 1), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x + 1), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x + 1), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x + 2), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x + 2), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x + 2), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x + 2), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x + 2), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x + 2), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x + 2), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x + 2), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x + 2), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x + 2), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x + 2), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x + 2), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x - 1), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x - 1), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x - 1), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x - 1), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x - 1), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x - 1), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x - 1), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x - 1), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x - 1), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x - 1), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x - 1), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x - 1), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x - 2), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x - 2), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x - 2), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x - 2), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x - 2), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x - 2), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x - 2), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x - 2), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x - 2), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x - 2), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x - 2), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x - 2), int(ArrowRightPoint1.y), color);
};




Background::Background()
{
	Init();
}
Background::~Background() {
	delete playerRoad;
	for (int i = 0; i < 12; i++) {
		delete window[i];
	}
}

//背景の初期化
void Background::Init() {

	playerScreenX = 0.0f;
	scrollX = 0.0f;
	offsetX = 0;
	startIdx = 0;

	playerRoad = new(PlayerRoad);

	for (int i = 0; i < 6; i++) {
		changeNum[i] = {};
		changeClockClock[i] = {};
		changeClockTime[i] = { 60 };
		yMoveNum[i] = int(rand() % 6);
	}

	changeClockClock[0] = 60;
	changeClockClock[1] = 50;
	changeClockClock[2] = 40;
	changeClockClock[3] = 30;
	changeClockClock[4] = 20;
	changeClockClock[5] = 10;

	for (int i = 0; i < MAX_NUM; i++) {
		scroll_factor[i] = 0.0f;
		seed[i] = rand() % 100 + 50;
		if (i >= 1) {
			sum[i] = sum[i - 1] + seed[i];
		}
	}


	for (int i = 0; i < 12; i++) {
		window[i] = new Obj;
	}

	window[0]->Init(120, 100); window[0]->pos_ = { 100, 350 };
	window[1]->Init(90, 110); window[1]->pos_ = { 450, 450 };
	window[2]->Init(180, 120); window[2]->pos_ = { 900, 370 };
	window[3]->Init(75, 90); window[3]->pos_ = { 1300, 430 };
	window[4]->Init(50, 105); window[4]->pos_ = { 1500, 310 };
	window[5]->Init(110, 115); window[5]->pos_ = { 2000, 450 };
	window[6]->Init(140, 95); window[6]->pos_ = { 2500, 340 };
	window[7]->Init(170, 100); window[7]->pos_ = { 2800, 500 };
	window[8]->Init(60, 120); window[8]->pos_ = { 3100, 320 };
	window[9]->Init(130, 105); window[9]->pos_ = { 3600, 470 };
	window[10]->Init(100, 90); window[10]->pos_ = { 4000, 350 };
	window[11]->Init(80, 100); window[11]->pos_ = { 4500, 370 };
};

//背景の更新処理
void Background::Update(Player* player, Map* map, char keys[256]) {

	if (player == nullptr || map == nullptr) {
		return;
	}

	//スクロール位置をループさせる
	if (scrollX < 0.0f) {
		scrollX += WINDOW_WIDTH * MAX_SCROLL;
	}
	if (scrollX >=  WINDOW_WIDTH * MAX_SCROLL) {
		scrollX -= WINDOW_WIDTH * MAX_SCROLL;
	}

	// ウィンドウのスクロール位置をループさせる
	for (int i = 0; i < 12; i++) {
		if (window[i]->pos_.x < -window[i]->width_) {
			window[i]->pos_.x += MID_WIDTH - window[i]->width_;
		}
		if (window[i]->pos_.x >= MID_WIDTH) {
			window[i]->pos_.x -= MID_WIDTH + window[i]->width_;
		}
	}

	offsetX = -(static_cast<int>(scrollX) % static_cast<int>(WINDOW_WIDTH));
	startIdx = static_cast<int>(scrollX) / static_cast<int>(WINDOW_WIDTH);


	if (map->block[(int)player->posNum.y][(int)player->posNum.x] == 2) {
		if (keys[DIK_A]) {
			scrollX -= OUTER_BG_SPEED;
			player->isPlayerLeft = true;
		} else {
			player->isPlayerLeft = false;
		}
		if (keys[DIK_D]) {
			scrollX += OUTER_BG_SPEED;
			player->isPlayerRight = true;
		} else {
			player->isPlayerRight = false;
		}
	}

	/////////////////////////////背景処理
///数字の更新
	for (int i = 0; i < 6; i++) {
		if (changeClockClock[i] != 0) {
			changeClockClock[i]--;
		}
		else {
			changeClockClock[i] = changeClockTime[i];
		}
		if (changeClockClock[i] % 15 == 0) {
			changeNum[i] = int((changeNum[i] + rand()) % 2);
		}
	}

};

//プレイヤーの移動によってスクロール関数
void Background::Scroll(Player* player, char keys[256]) {

	for (int j = 0; j < MAX_NUM; j++) {
		if (player->isPlayerLeft) {
			if (keys[DIK_A]) {
				scroll_factor[j] += OUTER_BG_SPEED;
			}
		}
		if (player->isPlayerRight) {
			if (keys[DIK_D]) {
				scroll_factor[j] -= OUTER_BG_SPEED;
			}
		}
	}

	// ウィンドウの位置更新
	for (int i = 0; i < 12; ++i) {
		if (player->isPlayerLeft) {
			if (keys[DIK_A]) {
				window[i]->pos_.x += MID_BG_SPEED;
			}
		}

		if (player->isPlayerRight && keys[DIK_D]) {
			if (keys[DIK_D]) {
				window[i]->pos_.x -= MID_BG_SPEED;
			}
		}
	}

}

//背景の描画処理
void Background::Render(Player* player) {

	if (player == nullptr) {
		return;
	}

	{
		int line1 = 208;
		int line2 = 250;
		int line3 = 305;
		int line4 = 380;
		int line5 = 470;

		Novice::DrawBox(0, 0, 1280, line1, 0.0f, 0x191b19FF, kFillModeSolid);
		Novice::DrawBox(0, line1, 1280, line2 - line1, 0.0f, 0x161816FF, kFillModeSolid);
		Novice::DrawBox(0, line2, 1280, line3 - line2, 0.0f, 0x191b19FF, kFillModeSolid);
		Novice::DrawBox(0, line3, 1280, line4 - line3, 0.0f, 0x1b1e1bFF, kFillModeSolid);
		Novice::DrawBox(0, line4, 1280, line5 - line4, 0.0f, 0x1d201dFF, kFillModeSolid);
		Novice::DrawBox(0, line5, 1280, 720 - line5, 0.0f, 0x232a23FF, kFillModeSolid);
	}

	playerRoad->render(player, 0xFFFFFFFF);

	///背景の数字
	{
		int numSizeW = 20;
		int numSizeH = int(20 * 1.4f);
		int colorStart = 0x4BBC5444;
		int colorEnd = 0x4BBC5400;
		for (int j = 0; j < MAX_NUM; j++) {
			for (int k = 0; k < 6; k++) {

				//スクロール位置をループさせる
				if (scroll_factor[j] < -(numSizeW + 5) - sum[j]) {
					scroll_factor[j] += WINDOW_WIDTH * MAX_SCROLL;
				}
				if (scroll_factor[j] >= WINDOW_WIDTH * MAX_SCROLL - (numSizeW + 5) - sum[j]) {
					scroll_factor[j] -= WINDOW_WIDTH * MAX_SCROLL;
				}

				int l = int(((k * j + (yMoveNum[k])) % 6));
				int m = k - yMoveNum[int(j % 6)];
				if (l < 0) { l *= -1; }	
				if (m < 0) { m += 6; }
				DrawNum(int((numSizeW + 5) + sum[j] + scroll_factor[j]), int(numSizeH / 2 + (numSizeH + 5) * k), numSizeW, colorChanger(colorStart, colorEnd, changeClockClock[5 - m], changeClockTime[5 - m]), changeNum[5 - l]);
			}
		}
	}
};

void Background::DrawMid() {
	///背景のWINDOW
	{
		for (int i = 0; i < 12; ++i) {
			window[i]->drawWindow(0x4BBC5444);
		}
	}
}
