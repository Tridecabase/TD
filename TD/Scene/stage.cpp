#include "stage.h"

//コンストラクタ
Stage::Stage()
	: background(new Background), map(new Map), player(new Player()),bulletA(new BulletA),bulletB(new BulletB), enemy(new Enemy()) {}
//デストラクタ
Stage::~Stage() {
	delete background;
	delete player;
	delete bulletA;
	delete bulletB;
	delete map;
	delete enemy;
}

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Init() {

	//背景の初期化
	background->Init();
	//プレイヤーの初期化
	player->Init(map);
	bulletA->Init();
	bulletB->Init();
	map = new Map;
	//敵の初期化
	enemy->Init();
};

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
	bulletA->Shot(player, map);
	bulletB->Shot(player, map);
	bulletA->Scroll(player, keys);
	bulletB->Scroll(player, keys);
	//敵の移動処理
	enemy->Move(bulletA,bulletB);
};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Render() {

	//背景の描画
	background->Render();
	//プレイヤーの描画
	player->Draw();
	//敵の描画
	enemy->Draw();
	//プレイヤーマップの描画
	
	//プレイヤー弾丸の描画
 	bulletA->Draw();
	bulletB->Draw();

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////