#include <Novice.h>
#include "UI.h"

UI::UI()
	:mouse(new Mouse) {};

UI::~UI() {
	delete mouse;
}

void UI::Updata() {
	mouse->Updata();
}

void UI::Draw() {
	mouse->Draw();
}


void Mouse::Updata()
{
	int x = 0;
	int y = 0;
	Novice::GetMousePosition(&x, &y);
	mousePos_ = { float(x),float(y) };
};

void Mouse::Draw()
{
	const int L = 10;
	int color = 0x4bbc54FF;
	int LTX = int(mousePos_.x) - L;
	int LTY = int(mousePos_.y) - L;
	int RTX = int(mousePos_.x) + L;
	int RTY = int(mousePos_.y) - L;
	int LBX = int(mousePos_.x) - L;
	int LBY = int(mousePos_.y) + L;
	int RBX = int(mousePos_.x) + L;
	int RBY = int(mousePos_.y) + L;
	Novice::SetMouseCursorVisibility(false);
	Novice::DrawLine(LTX-1, LTY, LTX + L/2, LTY, color);
	Novice::DrawLine(LTX, LTY, LTX, LTY + L / 2, color);

	Novice::DrawLine(RTX, RTY, RTX - L / 2, RTY, color);
	Novice::DrawLine(RTX, RTY, RTX, RTY + L / 2, color);

	Novice::DrawLine(LBX, LBY, LBX + L / 2, LBY, color);
	Novice::DrawLine(LBX, LBY, LBX, LBY - L / 2, color);

	Novice::DrawLine(RBX, RBY, RBX - L / 2, RBY, color);
	Novice::DrawLine(RBX, RBY, RBX, RBY - L / 2, color);

	Novice::DrawLine(int(mousePos_.x) + 15, int(mousePos_.y), int(mousePos_.x) - 15, int(mousePos_.y), color);
	Novice::DrawLine(int(mousePos_.x), int(mousePos_.y) + 15, int(mousePos_.x), int(mousePos_.y) - 15, color);

	//Novice::ScreenPrintf(10, 150, "MousePx = %d,MousePy = %d", int(mousePos_.x), int(mousePos_.y));

};