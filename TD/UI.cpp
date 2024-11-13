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

	int color = 0x4bbc54FF;
	int LTX = int(mousePos_.x) - 10;
	int LTY = int(mousePos_.y) - 10;
	int RTX = int(mousePos_.x) + 10;
	int RTY = int(mousePos_.y) - 10;
	int LBX = int(mousePos_.x) - 10;
	int LBY = int(mousePos_.y) + 10;
	int RBX = int(mousePos_.x) + 10;
	int RBY = int(mousePos_.y) + 10;
	Novice::SetMouseCursorVisibility(false);
	Novice::DrawLine(LTX, LTY, LTX + 5, LTY, color);
	Novice::DrawLine(LTX, LTY, LTX, LTY + 5, color);

	Novice::DrawLine(RTX, RTY, RTX - 5, RTY, color);
	Novice::DrawLine(RTX, RTY, RTX, RTY + 5, color);

	Novice::DrawLine(LBX, LBY, LBX + 5, LBY, color);
	Novice::DrawLine(LBX, LBY, LBX, LBY - 5, color);

	Novice::DrawLine(RBX, RBY, RBX - 5, RBY, color);
	Novice::DrawLine(RBX, RBY, RBX, RBY - 5, color);

	Novice::DrawLine(int(mousePos_.x) + 15, int(mousePos_.y), int(mousePos_.x) - 15, int(mousePos_.y), color);
	Novice::DrawLine(int(mousePos_.x), int(mousePos_.y) + 15, int(mousePos_.x), int(mousePos_.y) - 15, color);

	Novice::ScreenPrintf(10, 150, "MousePx = %d,MousePy = %d", int(mousePos_.x), int(mousePos_.y));

};