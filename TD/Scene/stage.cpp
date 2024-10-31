#include "stage.h"

Stage::Stage()
{

}
Stage::~Stage() {}

//ステージの初期化
void Stage::Init() {

	//背景の初期化
	background->Init();

};

//ステージの更新処理
void Stage::Update() {

	//背景の初期化
	background->Update();

};

//ステージの描画処理
void Stage::Render() {

	//背景の初期化
	background->Render();

};


/// /////////////////////
void Stage::MainStage(Player* player, Bullet* bullet, Map* map, char keys[], char preKeys[]) {
	player->Move(map, keys, preKeys);
	player->Draw(map);

	bullet->Shot(player, map);
	bullet->Draw();

	map->Draw();
}
////////////////////////////////