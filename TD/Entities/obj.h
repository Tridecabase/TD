#ifndef OBJ_H
#define OBJ_H

#include <Vector2.h>

class Obj
{
public:

	Obj();
	void Init(float width, float height);
	void drawWindow(int color);
	void drawChase(int color);

	Vector2 pos_;
	float height_;
	float width_;
	bool isAlive_;
};

#endif
