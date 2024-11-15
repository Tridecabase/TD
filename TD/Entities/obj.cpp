#include <Novice.h>
#include "obj.h"

void Obj::updateMouseUI()
{
	int* x = 0;
	int* y = 0;
	Novice::GetMousePosition(x, y);
	pos_.x = float(*x);
	pos_.y = float(*y);
};

void Obj::drawMouseUI()
{
	int color = 0x4bbc54FF;
	int x = 0;
	int y = 0;
	Novice::GetMousePosition(&x, &y);
	int LTX = x - 10;
	int LTY = y - 10;
	int RTX = x + 10;
	int RTY = y - 10;
	int LBX = x - 10;
	int LBY = y + 10;
	int RBX = x + 10;
	int RBY = y + 10;
	Novice::SetMouseCursorVisibility(false);
	Novice::DrawLine(LTX, LTY, LTX + 5, LTY, color);
	Novice::DrawLine(LTX, LTY, LTX, LTY + 5, color);

	Novice::DrawLine(RTX, RTY, RTX - 5, RTY, color);
	Novice::DrawLine(RTX, RTY, RTX, RTY + 5, color);

	Novice::DrawLine(LBX, LBY, LBX + 5, LBY, color);
	Novice::DrawLine(LBX, LBY, LBX, LBY - 5, color);

	Novice::DrawLine(RBX, RBY, RBX - 5, RBY, color);
	Novice::DrawLine(RBX, RBY, RBX, RBY - 5, color);

	Novice::DrawLine(x + 15, y, x - 15, y, color);
	Novice::DrawLine(x, y + 15, x, y - 15, color);

	Novice::ScreenPrintf(10, 150, "MousePx = %d,MousePy = %d", x, y);
};