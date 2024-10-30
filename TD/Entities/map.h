#pragma once
#include "Vector2.h"

class Map {
public:

	Map();

	Vector2 blockPos;
	float blockSize;
	int blockMapHandle;

	int block[5][5] = {
		{1,1,1,1,1},
		{2,0,0,0,2},
		{2,0,0,0,2},
		{2,0,0,0,2},
		{1,1,1,1,1}
	};
	
	void Draw();
};