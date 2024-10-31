#pragma once
#include "Vector2.h"
#include "map.h" 

class Player {
public:

	Player(Map* map);

	Vector2 pos;
	Vector2 tmpPos;
	Vector2 posNum;
	Vector2 speed;
	float width;
	float height;

	int shootCoolTime;
	bool isShootAble;

	bool isAlive;

	void Move(Map* map, char keys[], char preKeys[]);
	void Draw(Map* map);
}; #pragma once
