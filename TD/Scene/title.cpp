﻿#include "title.h"

Title::Title() {
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

Title::~Title() {

	delete ui;
	for (int i = 0; i < 4; i++) {
		delete window[i];
	}
	delete runingBinary;
	delete player;
}

void Title::Init() {
	srand((unsigned int)time(NULL));

	ui = new(UI);

	window[0]->Init(600, 0);
	window[0]->pos_ = { WINDOW_WIDTH / 2,600 };
	window[1]->Init(300, 0);
	window[1]->pos_ = { WINDOW_WIDTH / 2 - 320,530 };
	window[2]->Init(200, 0);
	window[2]->pos_ = { WINDOW_WIDTH / 2 + 300,150 };
	window[3]->Init(400, 0);
	window[3]->pos_ = { WINDOW_WIDTH / 2 + 300,670 };

	runingBinary->Init(180, 270, 270, 200, 20, 10);


	openTime = 15;
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
	player->screen_pos = { 1050 ,600 };
	player->width = 48.0f;
	player->height = 24.0f;
	player->clock = 0;
	player->timer = 1;
}

void Title::DrawTitle(const int posX, const int posY, const int width, int color) {
	char b[] = "NeoHorizon";
	float w = float(float(width) / 41.0f);
	float number = 0;
	for (int i = 0; i < 10; i++) {
		if (isupper(b[i])) {
			DrawApla(int(posX + (w * 5 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 5), color, b[i]);
			number += 6.0f;
		}
		if (islower(b[i])) {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
		}
	}
}

void Title::DrawGameStart(const int posX, const int posY, const int width, int color) {
	char b[] = "Click to start";
	float w = float(float(width) / 47.0f);
	float number = 0;
	for (int i = 0; i < 14; i++) {
		if (isupper(b[i])) {
			DrawApla(int(posX + (w * 5 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 5), color, b[i]);
			number += 6.0f;
		}
		if (islower(b[i])) {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
		}
		if (b[i] == ' ') {
			number += 2.0f;
		}
	}
}

void Title::DrawRule(const int posX, const int posY, const int width, int color) {
	char b[] = "WASD:Move ML:AttackL MR:AttackR Wheel:ChangeAttack";
	float w = float(float(width) / 215.0f);
	float number = 0;
	for (int i = 0; i < 50; i++) {
		if (isupper(b[i])) {
			DrawApla(int(posX + (w * 5 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 5), color, b[i]);
			number += 6.0f;
		}
		if (islower(b[i])) {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
		}
		if (b[i] == ':') {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
		}
		if (b[i] == ' ') {
			number += 3.0f;
		}
	}
}


void Title::Update() {
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

	///window変形
	{
		float t = float(openClock) / float(openTime);
		window[0]->height_ = (t * 0 + (1 - t) * 500);
		window[1]->height_ = (t * 0 + (1 - t) * 300);
		window[2]->height_ = (t * 0 + (1 - t) * 140);
		window[3]->height_ = (t * 0 + (1 - t) * 280);
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

bool Title::StageChanger() {
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

void Title::Render() {
	Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x191b19FF, kFillModeSolid);
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
	window[1]->drawWindow(0x4BBC54FF);
	if (openClock == 0) {
		runingBinary->Render(0x4BBC54FF);
	}
	///Window
	window[2]->drawWindow(0x4BBC54FF);
	///Window
	window[3]->drawWindow(0x4BBC54FF);
	if (openClock == 0) {
		player->Draw(0x4BBC54FF, false);
	}

	///WindowTitle
	window[0]->drawWindow(0x4BBC54FF);
	if (openClock == 0) {
		int y = 40;
		DrawTitle(360, 250 + y, 520, 0x4BBC54FF);
		DrawRule(353, 500 + y, 520, 0x4BBC54FF);
		if (aniClock <= (aniTime / 2)) {
			DrawGameStart(WINDOW_WIDTH / 2 - 150 - 25, 400 + y, 300, 0x4BBC54FF);
		}
	}

	ui->Draw();

	//Novice::ScreenPrintf(10, 680, "%d", scFlat);
	//Novice::ScreenPrintf(10, 700, "%d /%d", scClock, scTime);
	//Novice::ScreenPrintf(10, 700, "%d /%d", aniClock, aniTime);
	//Novice::ScreenPrintf(600, 600, "%d/%d", openClock, openTime);
	if (scFlat) {
		stageChangeShow(scClock, scTime, 0x4BBC54FF, 0);
	}

}
