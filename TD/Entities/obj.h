#pragma once
#include <Vector2.h>

class Obj
{
public:
	void updateMouseUI();
	void drawMouseUI();

	Vector2 pos_;
	bool isAlive_;
};

