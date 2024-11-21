#include "title.h"

Title::Title() {
	Window1 = {};
	w1Width = {};
	w1Height = {};
	Window2 = {};
	w2Width = {};
	w2Height = {};
	Window3 = {};
	w3Width = {};
	w3Height = {};
}

void Title::Init() {
}

void Title::Update() {
}

void Title::StageChanger(){
}

void Title::Render() {
	Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f,0x191b19FF, kFillModeSolid);

	DrawNum(500, 400, 50, 0x4BBC54FF,0);
	DrawNum(600, 400, 50, int(50 * 1.4f), 0x4BBC54FF, 5);
	DrawNum(500, 600, 50, 0x4BBC54FF,1);
}
