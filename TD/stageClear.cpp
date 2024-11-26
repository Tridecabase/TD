#include "StageClear.h"

StageClear::StageClear() {
	randNumber = {};

	ui = new(UI);

	for (int i = 0; i < 4; i++) {
		window[i] = new Obj;
	}
	runingBinary = new(RuningBinary);
	openClock = {};
	openTime = {};

	aniClock = {};
	aniTime = {};

	scClock = {};
	scTime = {};
	scFlat = {};

	for (int i = 0; i < 6; i++) {
		changeNum[i] = {};
		yMoveNum[i] = {};
		changeClockClock[i] = {};
		changeClockTime[i] = {};
	}

	player = new(Player);
}

StageClear::~StageClear() {

	delete ui;
	for (int i = 0; i < 4; i++) {
		delete window[i];
	}
	delete runingBinary;
	delete player;
}

void StageClear::Init() {
	srand((unsigned int)time(NULL));

	ui = new(UI);

	window[0]->Init(600, 0);
	window[0]->pos_ = { WINDOW_WIDTH / 2,600 };
	window[1]->Init(300, 0);
	window[1]->pos_ = { WINDOW_WIDTH / 2 - 320,530 };
	window[2]->Init(400, 0);
	window[2]->pos_ = { WINDOW_WIDTH / 2 + 400,320 };
	window[3]->Init(350, 0);
	window[3]->pos_ = { WINDOW_WIDTH / 2 + 420,670 };

	runingBinary->Init(180, 270, 270, 200, 20, 10);


	openTime = 60;
	openClock = openTime;

	aniClock = 0;
	aniTime = 60;

	scClock = 0;
	scTime = 60;
	scFlat = false;

	for (int i = 0; i < 6; i++) {
		changeNum[i] = {};
		changeClockTime[i] = { 60 };
		yMoveNum[i] = int(rand() % 6);
	}
	changeClockClock[0] = 60;
	changeClockClock[1] = 50;
	changeClockClock[2] = 40;
	changeClockClock[3] = 30;
	changeClockClock[4] = 20;
	changeClockClock[5] = 10;

	player->InitDisplay();
	player->velocity = 2;
	player->screen_pos = { 1030 ,600 };
	player->width = 48.0f;
	player->height = 24.0f;
	player->clock = 0;
	player->timer = 1;
}

void StageClear::DrawClear(const int posX, const int posY, const int width, int color) {
	char b[] = "GameClear";
	//char b[] = "e";
	float w = float(float(width) / 42.0f);
	float number = 0;
	for (int i = 0; i < 10; i++) {
		if (isupper(b[i])) {
			DrawApla(int(posX + (w * 5 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 5), color, b[i]);
			number += 6.0f;
		}
		if (islower(b[i])) {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
			if (b[i] == 'm') {
				number += 2.0f;
			}
		}
		if (b[i] == ' ') {
			number += 2.0f;
		}
	}

}
void StageClear::DrawCongratulations(const int posX, const int posY, const int width, int color) {
	char b[] = "Congratulations";
	//char b[] = "e";
	float w = float(float(width) / 66.0f);
	float number = 0;
	for (int i = 0; i < 16; i++) {
		if (isupper(b[i])) {
			DrawApla(int(posX + (w * 5 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 5), color, b[i]);
			number += 6.0f;
		}
		if (islower(b[i])) {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
			if (b[i] == 'm') {
				number += 2.0f;
			}
		}
		if (b[i] == ' ') {
			number += 2.0f;
		}
	}

}

void StageClear::DrawBack(const int posX, const int posY, const int width, int color) {
	char b[] = "Push M back to title";
	//char b[] = "e";
	float w = float(float(width) / 41.0f);
	float number = 0;
	for (int i = 0; i < 20; i++) {
		if (isupper(b[i])) {
			DrawApla(int(posX + (w * 5 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 5), color, b[i]);
			number += 6.0f;
		}
		if (islower(b[i])) {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
			if (b[i] == 'm') {
				number += 2.0f;
			}
		}
		if (b[i] == ' ') {
			number += 2.0f;
		}

	}

}

void StageClear::Update() {
	/////////////////////////////UI処理
	ui->Updata();

	/////////////////////////////opening処理
	///opening時計
	if (openClock != 0) {
		openClock--;
	}

	///aniClock
	if (aniClock != aniTime) {
		aniClock++;
	} else {
		aniClock = 0;
	}

	///
	if (aniClock <= aniTime / 3) {
		player->velocity = -2;
	} else if (aniClock <= aniTime / 3 * 2) {
		player->velocity = 0;
	} else if (aniClock > aniTime / 3 * 2) {
		player->velocity = 2;
	}

	///window変形
	{
		//float t = float(openClock) / float(openTime);
		window[0]->height_ = (500);
		window[1]->height_ = (300);
		window[2]->height_ = (300);
		window[3]->height_ = (280);
	}
	/////////////////////////////背景処理
	///数字の更新
	for (int i = 0; i < 6; i++) {
		if (changeClockClock[i] != 0) {
			changeClockClock[i]--;
		} else {
			changeClockClock[i] = changeClockTime[i];
		}
		if (changeClockClock[i] % 15 == 0) {
			changeNum[i] = int((changeNum[i] + rand()) % 2);
		}
	}

	runingBinary->Updata();
}

bool StageClear::StageChanger() {
	int MPX = {};
	int MPY = {};
	Novice::GetMousePosition(&MPX, &MPY);
	if (Novice::IsTriggerMouse(0)) {
		if (MPX > 0 && MPX < WINDOW_WIDTH) {
			if (MPY > 0 && MPY < WINDOW_HEIGHT) {
				if (!scFlat) {
					scFlat = true;
					scClock = scTime;
				}
			}
		}
	}
	if (scClock != 0) {
		scClock--;
	} else {
		if (scFlat == true) {
			return true;
		}
	}
	return false;
}

void StageClear::Render() {

	int color = 0x4BBC54FF;
	int colorYellow = 0xFFD306FF;
	int BlackColor = 0x191b19FF;

	Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, BlackColor, kFillModeSolid);
	///背景の数字
	{
		int numSizeW = 50;
		int numSizeH = int(50 * 1.4f);
		int colorStart = 0x4BBC5444;
		int colorEnd = 0x4BBC5400;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 27; j++) {
				for (int k = 0; k < 6; k++) {
					int l = int(((k * j + (yMoveNum[k])) % 6));
					int m = k - yMoveNum[int(j % 6)];
					if (l < 0) { l *= -1; }
					if (m < 0) { m += 6; }
					DrawNum(int((numSizeW + 5) * j + numSizeW / 2 - 10), int((numSizeH + 5) * 6 * i + numSizeH / 2 + (numSizeH + 5) * k), numSizeW, colorChanger(colorStart, colorEnd, changeClockClock[5 - m], changeClockTime[5 - m]), changeNum[5 - l]);

				}
			}
		}
	}

	///Window
	window[1]->drawWindow(color);
	//if (openClock == 0) {
		runingBinary->Render(colorYellow);
	//}
	///Window
	window[2]->drawWindow(color);
	//if (openClock == 0) {
	{
		//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x000055FF, kFillModeSolid);
		int line = 4;
		int MiddleW = 1035;
		int MiddleH = 130;
		int MainW = 100;
		int MainR = MainW / 2;

		///mimi
		int MainR2 = 40 / 2;
		Novice::DrawEllipse(MiddleW - MainW / 2, MiddleH - 10, MainR2, MainR2, 0.0f, colorYellow, kFillModeSolid);
		Novice::DrawEllipse(MiddleW - MainW / 2, MiddleH - 10, MainR2 - line, MainR2 - line, 0.0f, BlackColor, kFillModeSolid);

		Novice::DrawEllipse(MiddleW + MainW / 2, MiddleH - 10, MainR2, MainR2, 0.0f, colorYellow, kFillModeSolid);
		Novice::DrawEllipse(MiddleW + MainW / 2, MiddleH - 10, MainR2 - line, MainR2 - line, 0.0f, BlackColor, kFillModeSolid);

		///Main
		Novice::DrawEllipse(MiddleW, MiddleH, MainR, MainR, 0.0f, colorYellow, kFillModeSolid);
		Novice::DrawEllipse(MiddleW, MiddleH, MainR - line, MainR - line, 0.0f, BlackColor, kFillModeSolid);
		int BoxHeight = 60;
		Novice::DrawBox(MiddleW - MainW / 2, MiddleH - BoxHeight, MainW, BoxHeight, 0.0f, colorYellow, kFillModeSolid);
		Novice::DrawBox(MiddleW - MainW / 2 + line, MiddleH - BoxHeight + line, MainW - line * 2, BoxHeight - line, 0.0f, BlackColor, kFillModeSolid);

		///Leg
		int LegW = 20;
		int LegHeight = 40;
		Novice::DrawBox(MiddleW - LegW / 2, MiddleH + MainR - line, LegW, LegHeight, 0.0f, colorYellow, kFillModeSolid);
		Novice::DrawBox(MiddleW - LegW / 2 + line, MiddleH + MainR - line, LegW - line * 2, LegHeight, 0.0f, BlackColor, kFillModeSolid);
		int baseW = 60;
		int baseH = 30;
		Vector2 TPoint1 = { float(MiddleW), float(MiddleH + MainR - line + LegHeight - baseH / 2) };
		Vector2 TPoint2 = { float(MiddleW - baseW / 2), float(MiddleH + MainR - line + LegHeight + baseH / 2) };
		Vector2 TPoint3 = { float(MiddleW + baseW / 2), float(MiddleH + MainR - line + LegHeight + baseH / 2) };
		Novice::DrawTriangle(int(TPoint1.x), int(TPoint1.y), int(TPoint2.x), int(TPoint2.y), int(TPoint3.x), int(TPoint3.y), colorYellow, kFillModeSolid);
		Novice::DrawTriangle(int(TPoint1.x), int(TPoint1.y + line), int(TPoint2.x + line * 2), int(TPoint2.y - line), int(TPoint3.x - line * 2), int(TPoint3.y - line), BlackColor, kFillModeSolid);
		///LegCover
		Novice::DrawBox(MiddleW - LegW / 2 + line, MiddleH + MainR - line, LegW - line * 2, LegHeight, 0.0f, BlackColor, kFillModeSolid);

		DrawNum(MiddleW, MiddleH, 40, colorYellow, 1);
		DrawCongratulations(WINDOW_WIDTH / 2 + 400 - 290/2, MiddleH + 130, 290,colorYellow);
	}

	///Window
	window[3]->drawWindow(color);
	//if (openClock == 0) {
		player->Draw(color, false);
	//}

	///WindowTitle
	window[0]->drawWindow(color);
	//if (openClock == 0) {
		DrawClear(360, 290, 560, color);
		if (aniClock <= (aniTime / 2)) {
			DrawBack(WINDOW_WIDTH / 2 - 280, 440, 290, 0xFFD30688);
		}
	//}

	ui->Draw();

	//Novice::ScreenPrintf(10, 680, "%d", scFlat);
	//Novice::ScreenPrintf(10, 700, "%d /%d", scClock, scTime);
	//Novice::ScreenPrintf(10, 700, "%d /%d", aniClock, aniTime);
	//Novice::ScreenPrintf(600, 600, "%d/%d", openClock, openTime);
	if (scFlat) {
		stageChangeShow(scClock, scTime, 0x4BBC54FF, 0);
	}

	Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, colorChanger(0x4BBC54FF, 0x4BBC5400, openClock, openTime), kFillModeSolid);
	//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, colorChanger(0xFFFFFFFF, 0xFFFFFF00, openClock, openTime), kFillModeSolid);
	//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, colorChanger(0xFFD306FF, 0xFFD30600, openClock, openTime), kFillModeSolid);
	
}
