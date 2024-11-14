#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Characters/player.h"
#include "./Scene/background.h"
#include "./Tools/config.h"





typedef struct Bullet{
	Vector3 pos;
	Vector3 randPos;
	Vector3 savePos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 lastPos;
	Vector2 screen_pos;
	Vector2 shadowPos;
	int mousePosX;
	int mousePosY;
	float gravityY;
	float gravitySpeedY;
	float radius;
	float scale;
	float speed;
	float time;
	float distanceToMouse;
	float stoppageTime;
	float stoppageTimer;
	float altitude;

	bool isShoot;
}Bullet;


class BulletA {
public:

	BulletA();
	~BulletA();

	void Init();

	void Shot(Player* player, Map* map);

	void Scroll(Player* player, char keys[256]);

	void Draw() const;

	Vector2 getLastPos(float posZ1, float speed1, float distanceToMouse1, float frontPosX1, float frontPosY1, int mousePosX1, int mousePosY1) {
		Vector2 lastPos1 = {};
		Vector2 lastPos2 = {};
		Vector2 lastPos3 = {};
		float timer1 = 0.0f;
		float gravitySpeedY1 = 0.0f;
		while (posZ1 <= 1100.0f && timer1 <= 3.5f) {
			posZ1 += speed1;
			timer1 += speed1 / distanceToMouse1;
			lastPos1.x = (1 - timer1) * frontPosX1 + timer1 * mousePosX1;
			lastPos1.y = (1 - timer1) * frontPosY1 + timer1 * mousePosY1;
			if (timer1 >= 1.0f) {
				lastPos2.y += gravitySpeedY1;
				gravitySpeedY1 += 2.3f;
			}
		}
		lastPos3.x = lastPos1.x;
		lastPos3.y = lastPos1.y + lastPos2.y;
		return lastPos3;
	};

	Vector2 getShadowPos(Vector2 frontPos1, Vector2 lastPos1, Vector2 screenPos1) {
		Vector2 shadowPos1;
		shadowPos1.x = screenPos1.x;
		shadowPos1.y = ((frontPos1.y - lastPos1.y) / (frontPos1.x - lastPos1.x))*(screenPos1.x - frontPos1.x) + frontPos1.y;
		return shadowPos1;
	};

	Vector3 pos;
	Vector3 savePos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 lastPos;
	Vector2 screen_pos;
	Vector2 shadowPos;
	int mousePosX;
	int mousePosY;
	float gravityY;
	float gravitySpeedY;
	float radius;
	float scale;
	float speed;
	float time;
	float distanceToMouse;
	float altitude;
	
	bool isShoot;

	Bullet bulletA[MAX_BULLET_A]{};

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
	float radius;
	float scale;
	float speed;
	float time;
	float stoppageTime;
	float stoppageTimer;
	float distanceToMouse;

	bool isShoot;

	Bullet bulletB[MAX_BULLET_B]{};

};