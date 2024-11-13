#include "background.h"
#include <memory>

PlayerRoad::PlayerRoad() {
	if(true){
		float aa = 37.0f;
		float ab = 127.0f;
		float ba = 58.0f;
		float bb = 180.0f;

		///横線
		Line1P1 = { -1.0f, 530.0f };
		Line1P2 = { 1281.0f, 530.0f };
		Line2P1 = { -1.0f, 570.0f };
		Line2P2 = { 1281.0f, 570.0f };
		Line3P1 = { -1.0f, 618.0f };
		Line3P2 = { 1281.0f, 618.0f };
		Line4P1 = { -1.0f, 672.0f };
		Line4P2 = { 1281.0f, 672.0f };
		///縦線
		Line5P1 = { 640.0f - ab, 530.0f };
		Line5P2 = { 640.0f - bb, 672.0f };
		Line6P1 = { 640.0f - aa, 530.0f };
		Line6P2 = { 640.0f - ba, 672.0f };
		Line7P1 = { 640.0f + aa, 530.0f };
		Line7P2 = { 640.0f + ba, 672.0f };
		Line8P1 = { 640.0f + ab, 530.0f };
		Line8P2 = { 640.0f + bb, 672.0f };
	}

	if (true) {
		float a1 = 70.0f;
		float a2 = 100.0f;
		float b1 = 100.0f;
		float b2 = 130.0f;
		float c1 = 80.0f;
		float c2 = 110.0f;

		ArrowLeftPoint1 = {640.0f - a1, 530.0f};
		ArrowLeftPoint2 = {640.0f - a2, 530.0f};
		ArrowLeftPoint3 = {640.0f - b1, 601.0f};
		ArrowLeftPoint4 = {640.0f - b2, 601.0f};
		ArrowLeftPoint5 = {640.0f - c1, 672.0f};
		ArrowLeftPoint6 = {640.0f - c2, 672.0f};
	}

};

void PlayerRoad::render(int color) {
	///test
	Novice::DrawLine(640, 0,640, 720, color);
	///横線
	Novice::DrawLine(int(Line1P1.x), int(Line1P1.y), int(Line1P2.x), int(Line1P2.y), color);
	Novice::DrawLine(int(Line2P1.x), int(Line2P1.y), int(Line2P2.x), int(Line2P2.y), color);
	Novice::DrawLine(int(Line3P1.x), int(Line3P1.y), int(Line3P2.x), int(Line3P2.y), color);
	Novice::DrawLine(int(Line4P1.x), int(Line4P1.y), int(Line4P2.x), int(Line4P2.y), color);
	///縦線
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x), int(Line5P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x), int(Line6P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x), int(Line7P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x), int(Line8P2.y), color);

	///矢印(左)
	Novice::DrawLine(int(ArrowLeftPoint1.x), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x), int(ArrowLeftPoint1.y), color);
};




Background::Background()
{
	playerScreenX = 0.0f;
	scrollX = 0.0f;
	offsetX = 0;
	startIdx = 0;

	resourceManager.RegisterTexturesFromCSV("./Csv/background.csv");
	resourceManager.LoadTextures("bg");

	playerRoad = new(PlayerRoad);
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

	/*if (map->block[(int)player->posNum.y][(int)player->posNum.x] == 2) {
	}*/

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

	playerRoad->render(0xFFFFFFFF);

	Novice::ScreenPrintf(10, 60, "scollX %f", scrollX);
};