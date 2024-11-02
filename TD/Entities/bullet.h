#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Characters/player.h"

class Bullet {
public:

	Bullet();
	~Bullet();

	Vector3 pos;
	Vector2 newPos;
	Vector2 frontPos;
	int mousePosX;
	int mousePosY;
	float gravityY;
	float gravitySpeedY;
	float width;
	float height;
	float radius;
	float scale;
	float speed;
	float time;
	float distanceToMouse;
	int maxBullet;

	bool isShoot;

	void Shot(Player* player, Map* map);
	void Draw() const;
};