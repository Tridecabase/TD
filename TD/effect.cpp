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

Timer::Timer() {
	clock_ = 0;
	time_ = 0;
}

void Timer::Init0(int time) {
	clock_ = 0;
	time_ = time;
}

void Timer::InitM(int time) {
	clock_ = time;
	time_ = time;
}

void Timer::ToMix() {
	if (clock_ < time_) {
		clock_++;
	}
}

void Timer::ToMixZero() {
	if (clock_ < time_ - 1 && clock_ > 0) {
		clock_++;
	} else {
		clock_ = 0;
	};
}

void Timer::ToZero() {
	if (clock_ > 0) {
		clock_--;
	}
}


void Timer::ToZeroMix() {
	if (clock_ > 0 && clock_ < time_) {
		clock_--;
	} else {
		clock_ = time_;
	}
}

void Timer::foreverUp() {
	if (clock_ < time_ - 1) {
		clock_++;
	} else {
		clock_ = 0;
	}
}

void Timer::foreverDown() {
	if (clock_ > 0) {
		clock_--;
	} else {
		clock_ = time_;
	}
}

void Timer::AnimationF() {
	if (clock_ < time_ - 1) {
		clock_++;
	} else {
		clock_ = 0;
	}
}

int Timer::FrameChange() {
	return (clock_ / 5);
}




BoxV1::BoxV1()
	:startEndTimer(new Timer),
	holdTimer(new Timer)

{
	posX_ = {};
	posY_ = {};
	width_ = {};
	height_ = {};
}

BoxV1::~BoxV1() {
	delete holdTimer;
	delete startEndTimer;
}

void BoxV1::Init(const float MBW, const float MBH,
	const float MxW, const float MxH,
	const float MmW, const float MmH, int t, float* R) {
	srand((unsigned int)time(NULL));
	float MW = MxW - MmW;
	float MH = MxH - MmH;


	posX_ = float(int(rand() * *R) % int(MBW) - MBW / 2);
	*R += (posX_);
	if (*R < 0) { *R *= -1; }
	posY_ = float(int(rand() * *R) % int(MBH) - MBH / 2);
	*R += (posY_);
	if (*R < 0) { *R *= -1; }
	width_ = float(MmW + int(rand() * *R) % int(MW) - MW / 2);
	*R += (width_);
	if (*R < 0) { *R *= -1; }
	height_ = float(MmH + int(rand() * *R) % int(MH) - MH / 2);
	*R += (height_);
	if (*R < 0) { *R *= -1; }

	holdTimer->Init0(t);
	startEndTimer->clock_ = 1;
	startEndTimer->time_ = 15;
}

void BoxV1::Update() {
	if (holdTimer->clock_ == 0) {
		startEndTimer->ToMix();
	}
	if (startEndTimer->clock_ == startEndTimer->time_) {
		holdTimer->ToMix();
	}
	if (holdTimer->clock_ == holdTimer->time_) {
		startEndTimer->ToZero();
	}
}

void BoxV1::Render(const int posX, const int posY) {
	int line = 1;
	float width = {};
	float height = {};
	float t = float(startEndTimer->clock_) / float(startEndTimer->time_);
	if (holdTimer->clock_ != holdTimer->time_) {
		width = float((1 - t) * 1 + (t)*width_);
		height = height_;
	}
	if (holdTimer->clock_ == holdTimer->time_) {
		width = width_;
		height = float((1 - t) * 1 + (t)*height_);
	}
	Novice::DrawBox(int(posX + posX_ - width / 2), int(posY + posY_ - height / 2), int(width), int(height), 0.0f, 0xe51837FF, kFillModeSolid);
	Novice::DrawBox(int(posX + posX_ - width / 2 + line), int(posY + posY_ - height / 2 + line), int(width - line * 2), int(height - line * 2), 0.0f, 0xA30019FF, kFillModeSolid);

	//Novice::DrawBox(0, 0, 200, 100, 0.0f, 0x00000044, kFillModeSolid);
	//Novice::ScreenPrintf(10, 10, "startEndTimer");
	//Novice::ScreenPrintf(10, 30, "%d/%d", startEndTimer->clock_, startEndTimer->time_);
	//Novice::ScreenPrintf(10, 50, "holdTimer");
	//Novice::ScreenPrintf(10, 70, "%d/%d", holdTimer->clock_, holdTimer->time_);
}




digBox1::digBox1()
	:bornTimer(new Timer)
{
	spawnPosX_ = {};
	spawnPosY_ = {};
	boxMixWidth_ = {};
	boxMixHeight_ = {};
	boxMinWidth_ = {};
	boxMinHeight_ = {};
	width_ = {};
	height_ = {};
	for (int i = 0; i < 10; i++) {
		box[i] = new(BoxV1);
	}
	Rend_ = {};
}

digBox1::~digBox1() {
	for (int i = 0; i < 10; i++) {
		delete box[i];
	}
}


void digBox1::Init(const float SPX, const float SPY,
	const float MBW, const float MBH,
	const float MxW, const float MxH,
	const float MmW, const float MmH, const int t) {
	spawnPosX_ = SPX;
	spawnPosY_ = SPY;
	width_ = MBW;
	height_ = MBH;
	boxMixWidth_ = MxW;
	boxMixHeight_ = MxH;
	boxMinWidth_ = MmW;
	boxMinHeight_ = MmH;
	Rend_ = float(rand());
	for (int i = 0; i < 10; i++) {
		box[i] = new(BoxV1);
	}
	bornTimer->Init0(t);
}

void digBox1::Update() {
	bornTimer->foreverDown();
	if (bornTimer->clock_ == 0) {
		for (int i = 0; i < 10; i++) {
			if (box[i]->startEndTimer->clock_ == 0) {
				box[i]->Init(width_, height_, boxMixWidth_, boxMixHeight_, boxMinWidth_, boxMinHeight_, 120, &Rend_);
				break;
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		if (box[i]->startEndTimer->clock_ != 0) {
			box[i]->Update();
		}
	}


}

void digBox1::Render() {
	for (int i = 0; i < 10; i++) {
		if (box[i]->startEndTimer->clock_ != 0) {
			box[i]->Render(int(spawnPosX_), int(spawnPosY_));
		}

	}
	//Novice::DrawBox(10, 620, 200, 100, 0.0f, 0x00000044, kFillModeSolid);
	//Novice::ScreenPrintf(10, 640, "3=%f/%f", box[3]->posX_, box[3]->posY_);
	//Novice::ScreenPrintf(10, 660, "2=%f/%f", box[2]->posX_, box[2]->posY_);
	//Novice::ScreenPrintf(10, 680, "1=%f/%f", box[1]->posX_, box[1]->posY_);
	//Novice::ScreenPrintf(10, 700, "0=%f/%f", box[0]->posX_, box[0]->posY_);
}
