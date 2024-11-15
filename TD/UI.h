#pragma once
#include <Vector2.h>


class Mouse
{
public:
	void Updata();
	void Draw();

	Vector2 mousePos_;
};


class UI
{
public:
	UI();
	~UI();

	void Updata();
	void Draw();

	Mouse * mouse;
};