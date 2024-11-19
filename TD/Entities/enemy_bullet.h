#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "Vector2.h"
#include "Vector3.h"
#include "./Characters/enemy.h"
#include "./Scene/background.h"
#include "./Tools/config.h"

class FunnelBullet {
public:
	//コンストラクタとデストラクタ
	FunnelBullet();
	~FunnelBullet();

	typedef struct Bullet {
		Vector3 pos;
		Vector2 screen_pos;
		float gravityY;
		float gravitySpeedY;
		float radius;
		float scale;
		float speed;
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
	void Shot(Enemy* enemy);
	//プレイヤーの移動によってスクロール処理
	void Scroll(Player* player, char keys[256]);
	//描画処理
	void Draw();

	Bullet funnelBullet[MAX_BULLET_FUNNEL];

private:

};

#endif

