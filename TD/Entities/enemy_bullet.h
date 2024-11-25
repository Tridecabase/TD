#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "Vector2.h"
#include "Vector3.h"
#include "./Characters/enemy.h"
#include "./Scene/background.h"
#include "./Tools/config.h"
#include "./Tools/particle.h"

class FunnelBullet {
public:
	//コンストラクタとデストラクタ
	FunnelBullet();
	~FunnelBullet();

	typedef struct Bullet {
		Vector3 pos;
		Vector2 velocity;
		Vector2 target_pos;
		float gravityY;
		float gravitySpeedY;
		float radius;
		float scale;
		float speed;
		float angle;
		float time;
		int cooldown;
		float distanceToPlayer;
		float altitude;
		float frontAltitude;

		bool isShoot;
	}Bullet;

	//初期化
	void init();
	//発射処理
	void Shot(Player* player, Enemy* enemy);
	//プレイヤーの移動によってスクロール処理
	void Scroll(Player* player, char keys[256]);
	//描画処理
	void Draw();

	Bullet funnelBullet[MAX_BULLET_FUNNEL];

private:

	ParticleGenerator particle_generator;

};

class DroneBullet {
public:
	DroneBullet();
	~DroneBullet();

	typedef struct Bullet {
		Vector3 pos;
		Vector2 velocity;
		Vector2 target_pos;
		float radius;
		float scale;
		float speed;
		float angle;
		float time;
		int cooldown;
		bool isShoot;
	} Bullet;

	void init();
	void Shot(Player* player, Enemy* enemy);
	void Scroll(Player* player, char keys[256]);
	void Draw();

	Bullet droneBullets[MAX_BULLET_DRONE];

private:

};


#endif

