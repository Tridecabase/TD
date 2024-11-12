#include "background.h"
#include <memory>

Background::Background()
{
	playerScreenX = 0.0f;
	scrollX = 0.0f;
	offsetX = 0;
	startIdx = 0;

	resourceManager.RegisterTexturesFromCSV("./Csv/background.csv");
	resourceManager.LoadTextures("bg");
}
Background::~Background() {}

//背景の初期化
void Background::Init() {

	playerScreenX = 0.0f;
	scrollX = 0.0f;
	offsetX = 0;
	startIdx = 0;

};

//背景の更新処理
void Background::Update(Player* player, Map* map, char keys[256]) {

	//スクロール位置をループさせる
	if (scrollX < 0) {
		scrollX += totalWidth;
	}
	if (scrollX >= totalWidth) {
		scrollX -= totalWidth;
	}

	offsetX = -(static_cast<int>(scrollX) % static_cast<int>(WINDOW_WIDTH));
	startIdx = static_cast<int>(scrollX) / static_cast<int>(WINDOW_WIDTH);


	if (map->block[(int)player->posNum.y][(int)player->posNum.x] == 2) {
		if (keys[DIK_A]) {
			scrollX -= OUTER_BG_SPEED;
		}
		else if (keys[DIK_D]) {
			scrollX += OUTER_BG_SPEED;
		}
	}

	/*if (player->posNum.x <= 1.0f) {
		if (keys[DIK_A]) {
			scrollX -= OUTER_BG_SPEED;
		}
	}
	if (player->posNum.x >= 3.0f) {
		if (keys[DIK_D]) {
			scrollX += OUTER_BG_SPEED;
		}
	}*/
};

//背景の描画処理
void Background::Render() {

	for (int i = 0; i < 6; ++i) {
		int drawX = offsetX + i * static_cast<int>(WINDOW_WIDTH);

		int textureIdx = (startIdx + i) % 6 + 1;

		std::string textureName = std::to_string(textureIdx);
		resourceManager.Draw(drawX, 0, textureName, 1.0f, 1.0f, 0.0f, 0xffffffff);
	}

	Novice::ScreenPrintf(10, 60, "scollX %f", scrollX);
};