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

void RuningBinary::Init(const float posX, const float posY, const int showWidth, const int showHeight, const int wordWidth) {
	for (int i = 0; i < 20; i++) {
		wordFloat[i]->Init(wordWidth, i);
	}
	pos_ = { posX,posY };
	width_ = showWidth;
	height_ = showHeight;
	clock_ = 10;
	time_ = 10;
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

	Novice::ScreenPrintf(10, 700, "%d /%d", clock_, time_);
}

void RuningBinary::Render(){
	for (int i = 0; i < 20; i++) {
		if(wordFloat[i]->pos_ .y < height_){
			wordFloat[i]->Render(pos_.x, pos_.y, width_, clock_, time_, 0x4BBC54FF);
		}
		Novice::ScreenPrintf(10, 680 - i * 20, "%c", wordFloat[i]->word_[i]);
	}

}

