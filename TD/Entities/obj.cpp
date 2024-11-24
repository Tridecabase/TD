#include <Novice.h>
#include "obj.h"


Obj::Obj() {
	pos_ = {};
	height_ = {};
	width_ = {};
	isAlive_ = false;
}

void Obj::Init(float width, float height) {
	pos_ = {};
	height_ = height;
	width_ = width;
	isAlive_ = true;
};

void Obj::drawWindow(int color) {
	Vector2 center = { pos_.x ,pos_.y - height_ / 2 };
	int color2 = 0x191b19FF;

	Novice::DrawBox(int(pos_.x - width_ / 2), int(pos_.y - height_), int(width_), int(height_), 0.0f, color2, kFillModeSolid);
	Novice::DrawBox(int(pos_.x - width_ / 2), int(pos_.y - height_), int(width_), int(height_), 0.0f, color, kFillModeWireFrame);

	Novice::DrawBox(int(pos_.x + width_ / 2 - 20), int(pos_.y - height_), 20, int(height_), 0.0f, color, kFillModeWireFrame);
	Novice::DrawBox(int(pos_.x + width_ / 2 - 20), int(pos_.y - height_ + height_ / 3), 20, int(height_ / 6), 0.0f, color, kFillModeSolid);

	Novice::DrawBox(int(pos_.x - width_ / 2), int(pos_.y - height_), int(width_), 30, 0.0f, color, kFillModeSolid);
	Novice::DrawBox(int(pos_.x + width_ / 2 - 20 - 5), int(pos_.y - height_ + 5), 20, 20, 0.0f, color2, kFillModeWireFrame);
	Novice::DrawBox(int(pos_.x + width_ / 2 - 20 * 2 - 5 * 2), int(pos_.y - height_ + 5), 20, 20, 0.0f, color2, kFillModeWireFrame);
	Novice::DrawBox(int(pos_.x + width_ / 2 - 20 * 3 - 5 * 3), int(pos_.y - height_ + 5), 20, 20, 0.0f, color2, kFillModeWireFrame);



	//Novice::DrawEllipse(int(center.x), int(center.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
}

void Obj::drawChase(int color) {
	Vector2 center = { pos_.x ,pos_.y - height_ / 2 };
	int color2 = 0x191b19FF;

	Novice::DrawBox(int(pos_.x - width_ / 2), int(pos_.y - height_), int(width_), int(height_), 0.0f, color, kFillModeSolid);

	for (int i = 1; i < 5; i++) {
		Novice::DrawLine(int(pos_.x - width_ / 2 + width_ / 8 + ((width_ * 3 / 4) / 5 * i)), int(pos_.y - height_ + width_ / 8),
			int(pos_.x - width_ / 2 + width_ / 8 + ((width_ * 3 / 4) / 5 * i)), int(pos_.y - width_ / 8), color2);
	}

	Novice::DrawTriangle(int(pos_.x - width_ / 2 + width_ / 8 + ((width_ * 3 / 4) / 5)), int(pos_.y - height_ + width_ / 8),
		int(pos_.x - width_ / 2 + width_ / 8), int(pos_.y - height_ + width_ / 8),
		int(pos_.x + width_ / 2 - width_ / 8 - ((width_ * 3 / 4) / 5)), int(pos_.y - width_ / 8), color, kFillModeSolid);
	Novice::DrawTriangle(int(pos_.x - width_ / 2 + width_ / 8 + ((width_ * 3 / 4) / 5)), int(pos_.y - height_ + width_ / 8),
		int(pos_.x + width_ / 2 - width_ / 8), int(pos_.y - width_ / 8),
		int(pos_.x + width_ / 2 - width_ / 8 - ((width_ * 3 / 4) / 5)), int(pos_.y - width_ / 8),
		color, kFillModeSolid);


	Novice::DrawLine(int(pos_.x - width_ / 2 + width_ / 8 + ((width_ * 3 / 4) / 5)), int(pos_.y - height_ + width_ / 8),
		int(pos_.x + width_ / 2 - width_ / 8), int(pos_.y - width_ / 8), color2);
	Novice::DrawLine(int(pos_.x - width_ / 2 + width_ / 8), int(pos_.y - height_ + width_ / 8),
		int(pos_.x + width_ / 2 - width_ / 8 - ((width_ * 3 / 4) / 5)), int(pos_.y - width_ / 8), color2);

	Novice::DrawBox(int(pos_.x - width_ / 2 + width_ / 8), int(pos_.y - height_ + width_ / 8), int(width_ * 3 / 4), int(height_ - (width_ / 8) * 2), 0.0f, color2, kFillModeWireFrame);
	Novice::DrawBox(int(pos_.x - width_ / 2), int(pos_.y - height_), int(width_), int(height_), 0.0f, color2, kFillModeWireFrame);

	//Novice::DrawEllipse(int(center.x), int(center.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
}




WordFloat::WordFloat()
{
	for (int i = 0; i < 20; i++) {
		word_[i] = {};
	}
	pos_ = {};
	nPos_ = {};
	width_ = {};
	viewFlat_ = true;
}

void WordFloat::Init(const int wordWidth, const int Num) {
	char w[20][20] = { { "0110101001" },
					  { "101100100111" },
					  { "1101010001101" },
					  { "100111001" },
					  { "01101101001" },
					  { "1010100101" },
					  { "0101001101" },
					  { "110100110101" },
					  { "0110100111101" },
					  { "110101010" },
					  { "1011011001110" },
					  { "011010101" },
					  { "110101010110" },
					  { "10101100101" },
					  { "01010110010101" },
					  { "101010010101" },
					  { "100101101101" },
					  { "0110101001011" },
					  { "101010110111011" },
					  { "110101100101010" } };
	strcpy_s(word_, w[Num]);
	width_ = int(wordWidth);
	height_ = int(wordWidth * 1.4f);
	pos_.x = {};
	pos_.y = float((Num)*height_);
	if ((Num + 1) < 20) {
		nPos_.y = float((Num + 1) * height_);
	} else if ((Num + 1) == 20) {
		nPos_.y = float((0) * height_);
	}
	viewFlat_ = true;
}

void WordFloat::Updata(const int changeClock, bool flat) {

	if (changeClock == 0) {
		pos_.y = nPos_.y;
		nPos_.y += height_;
		viewFlat_ = true;
		if (flat) {
			nPos_.y -= height_ * 20;
			viewFlat_ = false;
		}
	}
}

void WordFloat::Render(const float posX, const float posY, const int showWidth, const int changeClock, const int changeTime, const int color) {
	int w = (width_ / 5);
	int number = 0;
	float t = float(changeClock) / float(changeTime);
	float y = (t)*pos_.y + (1 - t) * nPos_.y;
	if (viewFlat_) {
		for (int i = 0; i < 20; i++) {
			if (((float(width_) / 2) + w * number) < showWidth) {
				if (word_[i] == '0') {
					DrawNum(int(posX + (float(width_) / 2) + (w * number)), int(posY + y + float(height_) / 2), width_, color, 0);
					number += 6;
				} else if (word_[i] == '1') {
					DrawNum(int(posX + (float(width_) / 2) + (w * number)), int(posY + y + float(height_) / 2), width_, color, 1);
					number += 6;
				}
			}
		}
	}

}


