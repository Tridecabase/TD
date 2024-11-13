#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Characters/player.h"
#include "./Scene/background.h"
#include "./Tools/config.h"

class BulletA {
public:

	BulletA();
	~BulletA();

	void Init();

	void Shot(Player* player, Map* map);

	void Scroll(Player* player, char keys[256]);

	void Draw() const;

	Vector3 pos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 screen_pos;
	int mousePosX;
	int mousePosY;
	float gravityY;
	float gravitySpeedY;
	float width;
	float height;
	float depth;
	float radius;
	float scale;
	float speed;
	float time;
	float distanceToMouse;
	int maxBullet;

	bool isShoot;
};

class BulletB {
public:

	BulletB();
	~BulletB();

	void Init();

	void Shot(Player* player, Map* map);

	void Scroll(Player* player, char keys[256]);

	void Draw() const;

	Vector3 pos;
	Vector3 randPos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 screen_pos;
	int mousePosX;
	int mousePosY;
	float gravityY;
	float gravitySpeedY;
	float width;
	float height;
	float depth;
	float radius;
	float scale;
	float speed;
	float time;
	float stoppageTime;
	float distanceToMouse;
	int maxBullet;

	bool isShoot;

};