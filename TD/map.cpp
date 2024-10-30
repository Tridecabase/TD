#include <Novice.h>
#include "map.h" 

Map::Map() {

	blockSize = 96.0f;
	blockPos.x = 450.0f;
	blockPos.y = 450.0f;

	blockMapHandle = Novice::LoadTexture("./resources/map/blockMap.png");
}

void Map::Draw() {
	Novice::DrawSprite(static_cast<int>(blockSize/2 + blockPos.x -22.0f), static_cast<int>(blockSize / 3 + blockPos.y), blockMapHandle, 1.0f, 1.0f, 0.0f, WHITE);
}
