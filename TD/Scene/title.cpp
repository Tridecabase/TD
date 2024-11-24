﻿#include "title.h"

Title::Title() {
	randNumber = {};

	for (int i = 0; i < 4; i++) {
		window[i] = new Obj;
	}
	openClock = {};
	openTime = {};

	for (int i = 0; i < 6; i++) {
		changeNum[i] = {};
		yMoveNum[i] = {};
		changeClockClock[i] = {};
		changeClockTime[i] = {};
	}

}

Title::~Title() {
	for (int i = 0; i < 4; i++) {
		delete window[i];
	}
}

void Title::Init() {
	srand((unsigned int)time(NULL));

	window[0]->Init(600, 0);
	window[0]->pos_ = { WINDOW_WIDTH / 2,600 };
	window[1]->Init(300, 0);
	window[1]->pos_ = { WINDOW_WIDTH / 2 - 320,530 };
	window[2]->Init(200, 0);
	window[2]->pos_ = { WINDOW_WIDTH / 2 + 300,150 };
	window[3]->Init(400, 0);
	window[3]->pos_ = { WINDOW_WIDTH / 2 + 300,670 };

	openTime = 15;
	openClock = openTime;

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
}

void Title::DrawTitle(const int posX, const int posY,const int width, int color){
	char b[] = "NeoHorizon";
	//char b[] = "e";
	float w = float(float(width) / 41.0f);
	float number = 0;
	for (int i = 0; i < 10;i++) {
		if(isupper(b[i])) {
			DrawApla(int(posX + (w * 5 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 5), color, b[i]);
			number += 6.0f;
		}
		if (islower(b[i])) {
			DrawApla(int(posX + (w * 3 / 2) + (w * number)), int(posY + (w * 7 / 2)), int(w * 3), color, b[i]);
			number += 4.0f;
		}

	}

}

void Title::Update() {
	/////////////////////////////opening処理
	///opening時計
	if (openClock != 0) {
		openClock--;
	}

	///
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


}

void Title::StageChanger() {
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
	{
		window[1]->drawWindow(0x4BBC54FF);
		window[2]->drawWindow(0x4BBC54FF);
		window[3]->drawWindow(0x4BBC54FF);
		window[0]->drawWindow(0x4BBC54FF);
		Novice::ScreenPrintf(600, 600, "%d/%d", openClock, openTime);
	}

	///文字
	DrawTitle(360, 200,520, 0x4BBC54FF);
}
