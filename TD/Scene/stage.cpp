#include "stage.h"

//コンストラクタ
Stage::Stage()
	: background(new Background), map(new Map), player(new Player())  {}
//デストラクタ
Stage::~Stage() {
	delete background;
	delete player;
	delete map;
}

//ステージの初期化
void Stage::Init() {

	//背景の初期化
	background->Init();
	//プレイヤーの初期化
	player->Init(map);

};

//ステージの更新処理
void Stage::Update(char keys[256], char preKeys[256]) {

	//背景の更新処理
	background->Update();
	//プレイヤーの移動処理
	player->Move(map, keys, preKeys);
	//プレイヤー弾丸の更新処理
//	bullet->Shot(player, map);


};

//ステージの描画処理
void Stage::Render() {

	//背景の描画
	background->Render();
	//プレイヤーの描画
	player->Draw(map);
	//プレイヤーマップの描画
	map->Draw();
	//プレイヤー弾丸の描画
//	bullet->Draw();

};