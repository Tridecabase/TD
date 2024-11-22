#include "stage.h"

//コンストラクタ
Stage::Stage()
	: background(new Background), map(new Map), ui(new UI), player(new Player()),bullet(new Bullet),bulletA(new BulletA),bulletB(new BulletB), bulletC(new BulletC), bulletD(new BulletD), funnelBullet(new FunnelBullet), enemy(new Enemy()) {}
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
	ui = new UI;
	map = new Map;
	//敵の初期化
	enemy->Init();

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
	enemy->Move(bulletA,bulletB);
	enemy->Scroll(player, keys);
	//敵弾丸の更新処理
	enemy->UpdateFunnel(player, bulletA, bulletB);
	funnelBullet->Shot(player, enemy);
	funnelBullet->Scroll(player, keys);
	//UI処理
	ui->Updata();
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
	//プレイヤーマップの描画
	
	//プレイヤー弾丸の描画
 	bulletA->Draw();
	bulletB->Draw();
	bulletC->Draw();
	bulletD->Draw();


	//プレイヤーの描画
	player->Draw(0x4BBC54FF);

	//UIの描画
	ui->Draw();
};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////