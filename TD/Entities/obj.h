#ifndef OBJ_H
#define OBJ_H

#include <Vector2.h>
#include <string.h>
#include "drawPolygon.h"

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

class WordFloat
{
public:

	WordFloat();

	void Init(const int width, const int Num);
	void Updata(int changeClock, bool flat);
	void Render(const float posX, const float posY, const int showWidth, int changeClock, const int changeTime, const int color);


	///字
	char word_[20];
	///句のpos
	Vector2 pos_;
	Vector2 nPos_;
	int width_;
	int height_;
	bool viewFlat_;
};

#endif
