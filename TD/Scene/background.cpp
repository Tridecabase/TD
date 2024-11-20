#include "background.h"
#include <memory>

PlayerRoad::PlayerRoad() {
	{
		///横線用
		float y1 = 530.0f;
		float y2 = 572.0f;
		float y3 = 620.0f;
		float y4 = 682.0f;

		///縦線用
		float a1 = 45.0f;
		float a2 = 130.0f;
		float b1 = 63.0f;
		float b2 = 195.0f;

		///横線
		Line1P1 = { -1.0f, y1 };
		Line1P2 = { 1281.0f, y1 };
		Line2P1 = { -1.0f, y2 };
		Line2P2 = { 1281.0f, y2 };
		Line3P1 = { -1.0f, y3 };
		Line3P2 = { 1281.0f, y3 };
		Line4P1 = { -1.0f, y4 };
		Line4P2 = { 1281.0f, y4 };
		///縦線
		Line5P1 = { 640.0f - a2, y1 };
		Line5P2 = { 640.0f - b2, y4 };
		Line6P1 = { 640.0f - a1, y1 };
		Line6P2 = { 640.0f - b1, y4 };
		Line7P1 = { 640.0f + a1, y1 };
		Line7P2 = { 640.0f + b1, y4 };
		Line8P1 = { 640.0f + a2, y1 };
		Line8P2 = { 640.0f + b2, y4 };

		///矢印
		float c1 = 200.0f;
		float c2 = 170.0f;
		float d1 = 280.0f;
		float d2 = 250.0f;
		float e1 = 270.0f;
		float e2 = 240.0f;

		///左
		ArrowLeftPoint1 = { 640.0f - c1, y1 };
		ArrowLeftPoint2 = { 640.0f - c2, y1 };
		ArrowLeftPoint3 = { 640.0f - d1, 595.0f };
		ArrowLeftPoint4 = { 640.0f - d2, 595.0f };
		ArrowLeftPoint5 = { 640.0f - e1, y4 };
		ArrowLeftPoint6 = { 640.0f - e2, y4 };

		///右
		ArrowRightPoint1 = { 640.0f + c1, y1 };
		ArrowRightPoint2 = { 640.0f + c2, y1 };
		ArrowRightPoint3 = { 640.0f + d1, 595.0f };
		ArrowRightPoint4 = { 640.0f + d2, 595.0f };
		ArrowRightPoint5 = { 640.0f + e1, y4 };
		ArrowRightPoint6 = { 640.0f + e2, y4 };
	}

};

void PlayerRoad::render(Player* player, int color) {
	///test
	Novice::DrawLine(640, 0, 640, 720, color);
	///横線
	Novice::DrawLine(int(Line1P1.x), int(Line1P1.y), int(Line1P2.x), int(Line1P2.y), color);
	//Novice::DrawLine(int(Line2P1.x), int(Line2P1.y), int(Line2P2.x), int(Line2P2.y), color);
	//Novice::DrawLine(int(Line3P1.x), int(Line3P1.y), int(Line3P2.x), int(Line3P2.y), color);
	//Novice::DrawLine(int(Line4P1.x), int(Line4P1.y), int(Line4P2.x), int(Line4P2.y), color);
	DrawLineNew(Line2P1, Line2P2, 3, color);
	DrawLineNew(Line3P1, Line3P2, 5, color);
	DrawLineNew(Line4P1, Line4P2, 7, color);

	///縦線
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x + 1), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x - 1), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x + 2), int(Line5P2.y), color);
	Novice::DrawLine(int(Line5P1.x), int(Line5P1.y), int(Line5P2.x - 2), int(Line5P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x + 1), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x - 1), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x + 2), int(Line6P2.y), color);
	Novice::DrawLine(int(Line6P1.x), int(Line6P1.y), int(Line6P2.x - 2), int(Line6P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x + 1), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x - 1), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x + 2), int(Line7P2.y), color);
	Novice::DrawLine(int(Line7P1.x), int(Line7P1.y), int(Line7P2.x - 2), int(Line7P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x + 1), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x - 1), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x + 2), int(Line8P2.y), color);
	Novice::DrawLine(int(Line8P1.x), int(Line8P1.y), int(Line8P2.x - 2), int(Line8P2.y), color);


	///矢印(左)
	if (player->isPlayerLeft) {
		DrawPolygon(ArrowLeftPoint1, ArrowLeftPoint2, ArrowLeftPoint3, ArrowLeftPoint4, ArrowLeftPoint5, ArrowLeftPoint6, color);
	}
	Novice::DrawLine(int(ArrowLeftPoint1.x), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x + 1), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x + 1), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x + 1), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x + 1), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x + 1), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x + 1), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x + 1), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x + 1), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x + 1), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x + 1), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x + 1), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x + 1), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x + 2), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x + 2), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x + 2), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x + 2), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x + 2), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x + 2), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x + 2), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x + 2), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x + 2), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x + 2), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x + 2), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x + 2), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x - 1), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x - 1), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x - 1), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x - 1), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x - 1), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x - 1), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x - 1), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x - 1), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x - 1), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x - 1), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x - 1), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x - 1), int(ArrowLeftPoint1.y), color);

	Novice::DrawLine(int(ArrowLeftPoint1.x - 2), int(ArrowLeftPoint1.y), int(ArrowLeftPoint2.x - 2), int(ArrowLeftPoint2.y), color);
	Novice::DrawLine(int(ArrowLeftPoint2.x - 2), int(ArrowLeftPoint2.y), int(ArrowLeftPoint4.x - 2), int(ArrowLeftPoint4.y), color);
	Novice::DrawLine(int(ArrowLeftPoint4.x - 2), int(ArrowLeftPoint4.y), int(ArrowLeftPoint6.x - 2), int(ArrowLeftPoint6.y), color);
	Novice::DrawLine(int(ArrowLeftPoint6.x - 2), int(ArrowLeftPoint6.y), int(ArrowLeftPoint5.x - 2), int(ArrowLeftPoint5.y), color);
	Novice::DrawLine(int(ArrowLeftPoint5.x - 2), int(ArrowLeftPoint5.y), int(ArrowLeftPoint3.x - 2), int(ArrowLeftPoint3.y), color);
	Novice::DrawLine(int(ArrowLeftPoint3.x - 2), int(ArrowLeftPoint3.y), int(ArrowLeftPoint1.x - 2), int(ArrowLeftPoint1.y), color);


	///矢印(左)
	if (player->isPlayerRight) {
		DrawPolygon(ArrowRightPoint1, ArrowRightPoint2, ArrowRightPoint3, ArrowRightPoint4, ArrowRightPoint5, ArrowRightPoint6, color);
	}
	Novice::DrawLine(int(ArrowRightPoint1.x), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x + 1), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x + 1), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x + 1), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x + 1), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x + 1), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x + 1), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x + 1), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x + 1), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x + 1), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x + 1), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x + 1), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x + 1), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x + 2), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x + 2), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x + 2), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x + 2), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x + 2), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x + 2), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x + 2), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x + 2), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x + 2), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x + 2), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x + 2), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x + 2), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x - 1), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x - 1), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x - 1), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x - 1), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x - 1), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x - 1), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x - 1), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x - 1), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x - 1), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x - 1), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x - 1), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x - 1), int(ArrowRightPoint1.y), color);

	Novice::DrawLine(int(ArrowRightPoint1.x - 2), int(ArrowRightPoint1.y), int(ArrowRightPoint2.x - 2), int(ArrowRightPoint2.y), color);
	Novice::DrawLine(int(ArrowRightPoint2.x - 2), int(ArrowRightPoint2.y), int(ArrowRightPoint4.x - 2), int(ArrowRightPoint4.y), color);
	Novice::DrawLine(int(ArrowRightPoint4.x - 2), int(ArrowRightPoint4.y), int(ArrowRightPoint6.x - 2), int(ArrowRightPoint6.y), color);
	Novice::DrawLine(int(ArrowRightPoint6.x - 2), int(ArrowRightPoint6.y), int(ArrowRightPoint5.x - 2), int(ArrowRightPoint5.y), color);
	Novice::DrawLine(int(ArrowRightPoint5.x - 2), int(ArrowRightPoint5.y), int(ArrowRightPoint3.x - 2), int(ArrowRightPoint3.y), color);
	Novice::DrawLine(int(ArrowRightPoint3.x - 2), int(ArrowRightPoint3.y), int(ArrowRightPoint1.x - 2), int(ArrowRightPoint1.y), color);
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
			player->isPlayerLeft = true;
		} else {
			player->isPlayerLeft = false;
		}
		if (keys[DIK_D]) {
			scrollX += OUTER_BG_SPEED;
			player->isPlayerRight = true;
		} else {
			player->isPlayerRight = false;
		}
	}

};

//背景の描画処理
void Background::Render(Player* player) {

	for (int i = 0; i < MAX_SCROLL; ++i) {
		int drawX = offsetX + i * static_cast<int>(WINDOW_WIDTH);

		int textureIdx = (startIdx + i) % 6 + 1;

		std::string textureName = std::to_string(textureIdx);
		resourceManager.Draw(drawX, 0, textureName, 1.0f, 1.0f, 0.0f, 0xffffffff);
	}

	{
		int line1 = 208;
		int line2 = 250;
		int line3 = 305;
		int line4 = 380;
		int line5 = 470;

		Novice::DrawBox(0, 0, 1280, line1, 0.0f, 0x191b19FF, kFillModeSolid);
		Novice::DrawBox(0, line1, 1280, line2 - line1, 0.0f, 0x161816FF, kFillModeSolid);
		Novice::DrawBox(0, line2, 1280, line3 - line2, 0.0f, 0x191b19FF, kFillModeSolid);
		Novice::DrawBox(0, line3, 1280, line4 - line3, 0.0f, 0x1b1e1bFF, kFillModeSolid);
		Novice::DrawBox(0, line4, 1280, line5 - line4, 0.0f, 0x1d201dFF, kFillModeSolid);
		Novice::DrawBox(0, line5, 1280, 720 - line5, 0.0f, 0x232a23FF, kFillModeSolid);
	}

	playerRoad->render(player, 0xFFFFFFFF);

	Novice::ScreenPrintf(10, 60, "scollX %f", scrollX);

};