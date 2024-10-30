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

//void Obj::drawMouseUI()
//{
//	Novice::DrawBox((int)pos_.x, (int)pos_.y, 3, 3, 0.0f,0xFFFFFFFF,kFillModeSolid);
//
//}: