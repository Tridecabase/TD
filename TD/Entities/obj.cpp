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



	Novice::DrawEllipse(int(center.x), int(center.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
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

	Novice::DrawEllipse(int(center.x), int(center.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
}