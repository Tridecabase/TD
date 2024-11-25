#include "stage.h"

//コンストラクタ
Stage::Stage()
	: background(new Background), map(new Map), ui(new UI), player(new Player()),bullet(new Bullet),bulletA(new BulletA),bulletB(new BulletB), bulletC(new BulletC), bulletD(new BulletD), funnelBullet(new FunnelBullet), droneBullet(new DroneBullet), enemy(new Enemy()) {
	openTime = 60;
	openClock = openTime;

	aniClock = 0;
	aniTime = 60;

	scClock = 0;
	scTime = 60;
	scFlat = 0;
}
//デストラクタ
Stage::~Stage() {
	delete background;
	delete player;
	delete bullet;
	delete bulletA;
	delete bulletB;
	delete bulletC;
	delete bulletD;
	delete funnelBullet;
	delete droneBullet;
	delete map;
	delete enemy;
	delete ui;

}

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Init() {

	//背景の初期化
	background->Init();
	//プレイヤーの初期化
	player->Init(map);
	//プレイヤー弾丸の初期化
	bullet->Init();
	bulletA->Init();
	bulletB->Init();
	bulletC->Init();
	bulletD->Init();
	funnelBullet->init();
	droneBullet->init();
	ui = new UI;
	map = new Map;
	//敵の初期化
	enemy->Init();

	openTime = 60;
	openClock = openTime;

	aniClock = 0;
	aniTime = 60;

	scClock = 0;
	scTime = 60;
	scFlat = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Update(char keys[256], char preKeys[256]) {

	//背景の更新処理
	background->Update(player,map,keys);
	//プレイヤーの移動処理
	player->Move(map, keys, preKeys);
	//プレイヤー弾丸の更新処理
	bullet->Update();
	bulletA->Shot(player,bullet);
	bulletA->Scroll(player, keys);
	bulletB->Shot(player, bullet);
	bulletB->Scroll(player, keys);
	bulletC->Shot(player, bullet);
	bulletC->Scroll(player, keys);
	bulletD->Shot(player, bullet);
	bulletD->Scroll(player, keys);
	//敵の更新処理
	enemy->Move(player, bulletA, bulletB, bulletD);
	enemy->Scroll(player, keys);
	//敵弾丸の更新処理
	enemy->UpdateFunnel(player, bulletA, bulletB, bulletC, bulletD);
	funnelBullet->Shot(player, enemy);
	funnelBullet->Scroll(player, keys);
	droneBullet->Shot(player, enemy);
	droneBullet->Scroll(player, keys);
	//UI処理
	ui->Updata();

	///opening時計
	if (openClock != 0) {
		openClock--;
	}

	///aniClock
	if (aniClock != aniTime) {
		aniClock++;
	} else {
		aniClock = 0;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Render() {

	//背景の描画
	background->Render(player);
	//敵のUI描画
	enemy->DrawInfo();
	enemy->DrawFunnel();
	//敵の描画
	enemy->Draw();
	funnelBullet->Draw();
	droneBullet->Draw();
	//プレイヤーマップの描画
	
	//プレイヤー弾丸の描画
 	bulletA->Draw();
	bulletB->Draw();
	bulletC->Draw();
	bulletD->Draw();

	//プレイヤーの描画
	player->Draw(player->color1);

	//UIの描画
	ui->Draw();

	if (openClock != 0) {
		stageChangeShow(openClock, openTime, 0x4BBC54FF, 1);
	}
	
	if (scFlat) {
		stageChangeShow(scClock, scTime, 0x4BBC54FF, 0);
	}

	//Novice::ScreenPrintf(10, 680, "%d", scFlat);
	//Novice::ScreenPrintf(10, 700, "%d /%d", scClock, scTime);
	Novice::ScreenPrintf(10, 700, "%d /%d", aniClock, aniTime);
	//Novice::ScreenPrintf(600, 600, "%d/%d", openClock, openTime);
}
bool Stage::StageChanger(char key[256],char preKey[256])
{
	if (key[DIK_M] && !preKey[DIK_M]) {
		if (!scFlat) {
			scFlat = 1;
			scClock = scTime;
		}
	}
	if (scClock != 0) {
		scClock--;
	} else {
		if (scFlat > 0) {
			return true;
		}
	}
	return false;
}
;
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////