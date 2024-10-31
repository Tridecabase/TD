#include "title.h"

Title::Title(): angel_alpha(0.0f), angel_beta(0.0f), radius(0.0f), vel(0.0f)
{}
Title::~Title() {}

//背景の初期化
void Title::Init() {

	radius = 1400.0f;
	angel_alpha = DELTA_ANGEL * 165.0f;
	angel_beta = DELTA_ANGEL * 175.0f;
	vel = DELTA_ANGEL / 10.0f;
	line_alpha = 400.0f;
	line_beta = 500.0f;
	quad_width = 200.0f;
	quad_height = 100.0f;
	textureHandle = Novice::LoadTexture("./NoviceResources/white1x1.png");
};

//背景の更新処理
void Title::Update() {

	angel_alpha -= vel;
	angel_beta -= vel;

	if (angel_alpha > DELTA_ANGEL * 190.0f) {
		vel = -vel;
	}
	else if (angel_alpha < DELTA_ANGEL * 150.0f) {
		vel = -vel;
	}

};

//背景の描画処理
void Title::Render() {

	//Novice::DrawLine(
	//	static_cast<int>(TITLE_VIEW_POINT.x), 
	//	static_cast<int>(TITLE_VIEW_POINT.y), 
	//	static_cast<int>(TITLE_VIEW_POINT.x + radius * cosf(-angel_alpha)),
	//	static_cast<int>(TITLE_VIEW_POINT.y + radius * sinf(-angel_alpha)),
	//	0xffffffff);

	//Novice::DrawLine(
	//	static_cast<int>(TITLE_VIEW_POINT.x),
	//	static_cast<int>(TITLE_VIEW_POINT.y),
	//	static_cast<int>(TITLE_VIEW_POINT.x + radius * cosf(-angel_beta)),
	//	static_cast<int>(TITLE_VIEW_POINT.y + radius * sinf(-angel_beta)),
	//	0xffffffff);

	//底
	if (angel_alpha < DELTA_ANGEL * 180.0f && angel_alpha > DELTA_ANGEL * 90.0f) {
		Novice::DrawQuad(
			static_cast<int>(line_alpha - quad_width),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha) + quad_height),
			static_cast<int>(line_alpha),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha) + quad_height),
			static_cast<int>(line_beta - quad_width),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_beta) * (TITLE_VIEW_POINT.x - line_beta)),
			static_cast<int>(line_beta),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_beta) * (TITLE_VIEW_POINT.x - line_beta)),
			0, 0, 1, 1, textureHandle, 0x696969ff
		);
	}
	else if (angel_alpha > DELTA_ANGEL * 180.0f && angel_alpha < DELTA_ANGEL * 270.0f) {
		Novice::DrawQuad(
			static_cast<int>(line_alpha - quad_width),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha)),
			static_cast<int>(line_alpha),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha)),
			static_cast<int>(line_beta - quad_width),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_beta)),
			static_cast<int>(line_beta),
			static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_beta)),
			0, 0, 1, 1, textureHandle, 0xffffffff
		);
	}

	//正面
	Novice::DrawQuad(
		static_cast<int>(line_alpha - quad_width),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha)),
		static_cast<int>(line_alpha),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha)),
		static_cast<int>(line_alpha - quad_width),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha) + quad_height),
		static_cast<int>(line_alpha),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha) + quad_height),
		0,0,1,1,textureHandle, 0xf5f5f5ff
	);

	//側面
	Novice::DrawQuad(
		static_cast<int>(line_alpha),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha)),
		static_cast<int>(line_beta),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_beta)),
		static_cast<int>(line_alpha),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_alpha) * (TITLE_VIEW_POINT.x - line_alpha) + quad_height),
		static_cast<int>(line_beta),
		static_cast<int>(TITLE_VIEW_POINT.y + tanf(angel_beta) * (TITLE_VIEW_POINT.x - line_beta)),
		0, 0, 1, 1, textureHandle, 0xa9a9a9ff
	);

};