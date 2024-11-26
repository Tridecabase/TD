#include "effect.h"

RuningBinary::RuningBinary() {
	for (int i = 0; i < 20; i++) {
		wordFloat[i] = new(WordFloat);
	}
	pos_ = {};
	width_ = {};
	height_ = {};
	clock_ = 0;
	time_ = 0;
}

RuningBinary::~RuningBinary() {
	for (int i = 0; i < 20; i++) {
		delete wordFloat[i];
	}
}

void RuningBinary::Init(const float posX, const float posY, const int showWidth, const int showHeight, const int wordWidth, const int clock) {
	for (int i = 0; i < 20; i++) {
		wordFloat[i]->Init(wordWidth, i);
	}
	pos_ = { posX,posY };
	width_ = showWidth;
	height_ = showHeight;
	clock_ = clock;
	time_ = clock;
}

void RuningBinary::Updata() {
	if (clock_ != 0) {
		clock_--;
	}

	bool flat2 = false;
	for (int i = 0; i < 20; i++) {
		bool flat = false;
		if (!flat2) {
			if (i < 19) { if (wordFloat[i]->nPos_.y > wordFloat[i + 1]->nPos_.y) { flat = true; flat2 = true; } }
			if (i == 19) { if (wordFloat[i]->nPos_.y > wordFloat[0]->nPos_.y) { flat = true; flat2 = true; } }
		}
		wordFloat[i]->Updata(clock_, flat);
	}

	if (clock_ == 0) {
		clock_ = time_;
	}

	//Novice::ScreenPrintf(10, 700, "%d /%d", clock_, time_);
}

void RuningBinary::Render(const int color) {
	for (int i = 0; i < 20; i++) {
		if (wordFloat[i]->pos_.y < height_) {
			wordFloat[i]->Render(pos_.x, pos_.y, width_, clock_, time_, color);
		}
		//Novice::ScreenPrintf(10, 680 - i * 20, "%c", wordFloat[i]->word_[i]);
	}

}

void stageChangeShow(const int clock, const int time, const int color, int type) {
	if (type == 0) {
		float t = float(clock) / float(time);
		Vector2 p[5] = {};
		Vector2 pos[5] = {};
		Vector2 nPos[5] = {};
		for (int i = 0; i < 5; i++) {
			pos[i].y = float(0 + i * (WINDOW_HEIGHT / 5));
			nPos[i].y = pos[i].y;
			p[i].y = pos[i].y;

			pos[i].x = float(WINDOW_WIDTH + i * (WINDOW_WIDTH / 5));
			nPos[i].x = float(-WINDOW_WIDTH + i * (WINDOW_WIDTH / 5));

			p[i].x = float((t)*pos[i].x + (1 - t)*nPos[i].x);
		}
		for (int i = 0; i < 5; i++) {
			Novice::DrawBox(int(p[i].x),int(p[i].y), WINDOW_WIDTH * 2, WINDOW_HEIGHT / 5,0.0f,color,kFillModeSolid);
		}
		//Novice::ScreenPrintf(10, 660, "%f|%f|%f", p[0].x, pos[0].x, nPos[0].x);
	}
	if (type == 1) {
		float t = float(clock) / float(time);
		Vector2 p[5] = {};
		Vector2 pos[5] = {};
		Vector2 nPos[5] = {};
		for (int i = 0; i < 5; i++) {
			pos[i].y = float(0 + i * (WINDOW_HEIGHT / 5));
			nPos[i].y = pos[i].y;
			p[i].y = pos[i].y;

			pos[i].x = float(-WINDOW_WIDTH + i * (WINDOW_WIDTH / 5));
			nPos[i].x = float(-(WINDOW_WIDTH * 3) + i * (WINDOW_WIDTH / 5));

			p[i].x = float((t)*pos[i].x + (1 - t)*nPos[i].x);
		}
		for (int i = 0; i < 5; i++) {
			Novice::DrawBox(int(p[i].x),int(p[i].y), WINDOW_WIDTH * 2, WINDOW_HEIGHT / 5,0.0f,color,kFillModeSolid);
		}
		//Novice::ScreenPrintf(10, 660, "%f|%f|%f", p[0].x, pos[0].x, nPos[0].x);
	}
}
