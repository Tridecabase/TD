#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Characters/player.h"
#include "./Scene/background.h"
#include "./Tools/config.h"


typedef struct Bullet_A{
	Vector3 pos;
	Vector3 savePos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 lastPos;
	Vector2 screen_pos;
	int mousePosX;
	int mousePosY;
	float gravityY;
	float gravitySpeedY;
	float radiusX;
	float radiusY;
	float theta;
	float scale;
	float speed;
	float time;
	float distanceToMouse;

	bool isShoot;
}Bullet_A;

typedef struct Bullet_B {
	Vector3 pos;
	Vector3 randPos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 lastPos;
	Vector2 screen_pos;
	int mousePosX;
	int mousePosY;
	float radiusX;
	float radiusY;
	float scale;
	float speed;
	float time;
	float distanceToMouse;
	float stoppageTime;
	float stoppageTimer;

	bool isShoot;
}Bullet_B;

typedef struct Bullet_C {
	Vector3 pos;
	Vector3 randPos;
	Vector3 savePos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 lastPos;
	Vector2 screen_pos;
	int mousePosX;
	int mousePosY;
	float gravityY;
	float gravitySpeedY;
	float radiusX;
	float radiusY;
	float theta;
	float scale;
	float speed;
	float time;
	float distanceToMouse;

	bool isShoot;
}Bullet_C;

typedef struct Bullet_D {
	Vector3 pos;
	Vector3 randPos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 screen_pos;
	int mousePosX;
	int mousePosY;
	float radiusX;
	float radiusY;
	float scale;
	float speed;
	int randTime;
	float time;
	
	bool isShoot;
}Bullet_D;

class Bullet {
public:

	Bullet();
	~Bullet();

	void Init();

	void Update();

	int mouseValue;
	bool mouseType;

};

class BulletA {
public:

	BulletA();
	~BulletA();

	void Init();

	void Shot(Player* player, Bullet* bullet);

	void Scroll(Player* player, char keys[256]);

	void Draw() const;

	Vector2 getLastPos(float posZ1, float speed1, float distanceToMouse1, float frontPosX1, float frontPosY1, int mousePosX1, int mousePosY1) {
		Vector2 lastPos1 = {};
		Vector2 lastPos2 = {};
		Vector2 lastPos3 = {};
		float timer1 = 0.0f;
		float gravitySpeedY1 = 0.0f;
		while (posZ1 <= 1100.0f) {
			posZ1 += speed1;
			timer1 += speed1 / distanceToMouse1;
			lastPos1.x = (1 - timer1) * frontPosX1 + timer1 * mousePosX1;
			lastPos1.y = (1 - timer1) * frontPosY1 + timer1 * mousePosY1;
			if (timer1 >= 1.0f) {
				lastPos2.y += gravitySpeedY1;
				gravitySpeedY1 += 2.0f;
			}
		}
		lastPos3.x = lastPos1.x;
		lastPos3.y = lastPos1.y + lastPos2.y;
		return lastPos3;
	};

	/*Vector2 getShadowPos(Vector2 frontPos1, Vector2 lastPos1, Vector2 screenPos1) {
		Vector2 shadowPos1;
		shadowPos1.x = screenPos1.x;
		shadowPos1.y = ((frontPos1.y - lastPos1.y) * (screenPos1.x - frontPos1.x) / (frontPos1.x - lastPos1.x)) + frontPos1.y;
		return shadowPos1;
	};*/

	Bullet_A bulletA[MAX_BULLET_A]{};

};

class BulletB {
public:

	BulletB();
	~BulletB();

	void Init();

	void Shot(Player* player, Bullet* bullet);

	void Scroll(Player* player, char keys[256]);

	void Draw() const;

	Bullet_B bulletB[MAX_BULLET_B]{};

};


class BulletC {
public:

	BulletC();
	~BulletC();

	void Init();

	void Shot(Player* player, Bullet* bullet);

	void Scroll(Player* player, char keys[256]);

	void Draw() const;

	Vector2 getLastPos(float posZ1, float speed1, float distanceToMouse1, float frontPosX1, float frontPosY1, int mousePosX1, int mousePosY1) {
		Vector2 lastPos1 = {};
		Vector2 lastPos2 = {};
		Vector2 lastPos3 = {};
		float timer1 = 0.0f;
		float gravitySpeedY1 = 0.0f;
		while (posZ1 <= 800.0f) {
			posZ1 += speed1;
			timer1 += speed1 / distanceToMouse1;
			lastPos1.x = (1 - timer1) * frontPosX1 + timer1 * mousePosX1;
			lastPos1.y = (1 - timer1) * frontPosY1 + timer1 * mousePosY1;
			if (timer1 >= 1.0f) {
				lastPos2.y += gravitySpeedY1;
				gravitySpeedY1 += 3.0f;
			}
		}
		lastPos3.x = lastPos1.x;
		lastPos3.y = lastPos1.y + lastPos2.y;
		return lastPos3;
	};

	Bullet_C bulletC[MAX_SHELL_C][MAX_BULLET_C]{};

};

class BulletD {
public:

	BulletD();
	~BulletD();

	void Init();

	void Shot(Player* player, Bullet* bullet);

	void Scroll(Player* player, char keys[256]);

	void Draw() const;

	Vector3 pos;
	Vector2 newPos;
	Vector2 frontPos;
	Vector2 lastPos;
	Vector2 screen_pos;
	int mousePosX;
	int mousePosY;
	float radiusX;
	float radiusY;
	float scale;
	float speed;
	float time;
	float stoppageTime;
	float stoppageTimer;
	float distanceToMouse;

	bool isShoot;

	Bullet_D bulletD[MAX_BULLET_D]{};

};

//class FunnelBullet {
//public:
//	//コンストラクタとデストラクタ
//	FunnelBullet();
//	~FunnelBullet();
//
//	//初期化
//	void init();
//	//発射処理
//	void Shot();
//	//プレイヤーの移動によってスクロール処理
//	void Scroll();
//	//描画処理
//	void Draw() const;
//
//	Bullet funnelBullet[MAX_BULLET_FUNNEL];
//
//private:
//
//};


