#pragma once
#include "Vector2.h"
#include "./Characters/player.h"

class Bullet {
public:

	Bullet();
	~Bullet();

	Vector2 pos;
	Vector2 newPos;
	Vector2 frontPos;
	int mousePosX;
	int mousePosY;
	float width;
	float height;
	float radius;
	float speed;
	float time;
	float distanceToMouse;
	int maxBullet;

	bool isShoot;

	void Shot(Player* player, Map* map);
	void Draw() const;
};