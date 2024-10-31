#pragma once
#include "Vector2.h"
#include "./Entities/map.h" 
#include "./Tools/config.h" 

class Player {
public:

	Player();
	~Player();

	void Init(Map* map);
	void Move(Map* map, char keys[256], char preKeys[256]);
	void Draw(Map* map);

private:

	Vector2 pos;
	Vector2 tmpPos;
	Vector2 posNum;
	Vector2 speed;
	float width;
	float height;

	int shootCoolTime;
	bool isShootAble;

	bool isAlive;

}; 