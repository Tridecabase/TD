#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "./Tools/config.h" 
#include "./Tools/wave_generator.h" 
#include "./Characters/player.h" 
#include "./Entities/bullet.h"
#include <string>
#include <random>
#include <Novice.h>

//行動IDに基づいたBOSS行動モジュール
enum class ActionID {
	IDLE,					//待機
	MOVE_AND_DEPLOY,		//移動して浮遊砲を設置する行動
	FIRE_AT_PLAYER,			//プレイヤーに向けた弾を多方向に発射
	Figure_Eight,
	BREAK_STATE				//ブレイク状態
							//and more...
};


class Enemy {
public:

	//コンストラクタとデストラクタ
	Enemy();
	~Enemy();

	//敵の初期化
	void Init();
	//敵の移動処理
	void Move(Player* player, BulletA*bulletA, BulletB*bulletB, BulletC* bulletC, BulletD* bulletD);
	//敵の描画
	void Draw();
	//敵の情報を表示する関数
	void DrawInfo();
	//void RenderWaveWithLength(WaveGenerator* wave, int length, unsigned int color);


	//浮遊砲の更新処理
	void UpdateFunnel(Player* player, BulletA* bulletA, BulletB* bulletB, BulletC* bulletC, BulletD* bulletD);
	//浮遊砲を表示する関数
	void DrawFunnel() const;

	// ============================
	// 敵の攻撃行動関数
	// ============================

	//行動をランダムに選択して実行
	void PerformAction();
	//ダメージを受けた際の処理
	void TakeDamage(int damage);
	//ブレイクゲージを更新
	void UpdateBreakMeter() const;

	//プレイヤーの移動によってスクロール関数
	void Scroll(Player* player, char keys[256]);

	//位置をループさせる
	void Loop(float &x) {
		if (x < 0.0f) {
			x += WINDOW_WIDTH * MAX_SCROLL;
		}
		if (x >= WINDOW_WIDTH * MAX_SCROLL) {
			x -= WINDOW_WIDTH * MAX_SCROLL;
		}
	}



	// ============================
	// 敵基本情報
	// ============================

	//BOSSの名前
	std::string name;
	//現在のHP
	int hp;
	//敵の位置ベクトル
	Vector3 pos;
	//敵の長さ
	float width;
	//敵の深さ
	float depth;
	//敵の高さ
	float height;
	//敵の速度
	float vel;
	//敵の色
	int color;
	//敵の生存フラグ
	bool isAlive;

	//現在の行動
	ActionID current_action;
	//行動の残り時間
	int action_timer;
	//ブレイクゲージ
	int break_meter;
	//ブレイクゲージの最大値
	int break_meter_max;
	//ブレイク状態フラグ
	bool is_break;
	//ブレイク状態の残り時間
	int break_timer;


	float tmp;

	// ============================
	// 弾丸関数変数
	// ============================

	//弾丸のクールダウン
	int shootCoolTime;
	//弾丸撃つのフラグ
	bool isShootAble;

	//浮遊砲構造体
	struct Funnel {
		bool isActive;       //浮遊砲が有効かどうか
		bool isHit;
		float x, y;			 //浮遊砲の位置
		float width, height; //浮遊砲のサイズ
		int hp;              //浮遊砲の耐久値
		unsigned int color;
		unsigned int line_color;
		float angle;
		Vector2 inner_center;//内円の中心位置
		Vector2 distance;	 //プレイヤーと内円の相対位置
		Vector2 eyeball;	 //目の位置
		float eyeball_r;	 //目の半径
		float angleToPlayer; //プレイヤーと内円の角度
		float floatTime;
	};

	//敵クラスのメンバー変数として宣言
	Funnel funnel[MAX_FUNNEL];

	const float angular_speed = 0.01f;


	// ============================
	// 背景用のメンバー変数を
	// ============================

	Vector2 screen_pos;

	struct Obj {
		Vector2 pos;		//位置
		Vector2 tmp_pos;	//位置
		Vector2 r;			//半径
		float angle;		//角度
		unsigned int color;	//色
		float tilt;			//運動傾斜角度
		float tilt_rad;		//傾斜角度のラジアン
		float w;			//中心点の回転角度
		float timer;		//回転カウンター
		Vector2 ellipse;	//楕円の半径
		Vector2 vel;		//速度
		float acc;			//加速度
	};

	struct Subobj {
		Vector2 pos;		//位置
		Vector2 tmp_pos;	//位置
		Vector2 r;			//半径
		float angle;		//角度
		unsigned int color;	//色
		Vector2 vel;		//速度
		float acc;			//加速度
	};

	// ============================
	// 敵描画変数
	// ============================

	Obj center;
	Obj drone1;
	Obj drone2;
	Obj drone3;

private:

	// ============================
	// 敵の攻撃行動管理
	// ============================

	bool is_spawned;

	//行動を切り替える関数
	void SetRandomAction();

	//行動を実行する関数
	//ID 100
	void Idle();
	//ID 101: 移動して浮遊砲を設置
	void MoveAndDeploy(); 
	void DeployFunnel(float x, float y);
	//ID 102: 弾を多方向に発射
	void FireAtPlayer();
	//ID 103
	void FigureEight();
	//and more...

	// ============================
	// ブレイク状態の管理
	// ============================

	//ブレイク状態に入る
	void EnterBreakState();
	//ブレイク状態を終了
	void ExitBreakState();

	// ============================
	// HP BAR 表示
	// ============================

	//線の数
	const int WAVE_NUMBERS = 1000;
	//振幅
	const int BASE_AMP = 4;
	//波長
	const int WAVE_LENGTH = 200;
	//速度
	const float WAVE_SPEED = 2.0f;
	//色
	const unsigned int BASE_COLOR = 0x00FF0044;

	int hpbar_r;
	int hpbar_g;
	int hpbar_b;
	int hpbar_alpha;

	WaveGenerator* wave1;
	WaveGenerator* wave2;
	WaveGenerator* wave3;


	// ============================
	// 敵描画変数
	// ============================

	Vector2 drone1_shift;
	Vector2 drone2_shift;

	Subobj drone_aura[3];
	Subobj drone_eye[3];



	// ============================
	// 敵運動関するローカル定数
	// ============================

	const float MAX_SPEED_ = 10.0f;
	const float ACCELERATION_ = 0.2f;
	const float DECELERATION_ = 0.2f;
	const float RESTORE_STRENGTH_ = 3.0f;
	const float MAX_FOLLOW_DISTANCE_ = 30.0f;

	// ============================
	// 敵運動関するベクトル計算関数
	// ============================

	Vector2 Add(const Vector2& a, const Vector2& b) {
		return { a.x + b.x, a.y + b.y };
	}

	Vector2 Subtract(const Vector2& a, const Vector2& b) {
		return { a.x - b.x, a.y - b.y };
	}

	Vector2 Multiply(const Vector2& v, float scalar) {
		return { v.x * scalar, v.y * scalar };
	}

	Vector2 Divide(const Vector2& v, float scalar) {
		return { v.x / scalar, v.y / scalar };
	}

	float Magnitude(const Vector2& v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	Vector2 Normalize(const Vector2& v) {
		float mag = Magnitude(v);
		return mag > 0.0f ? Divide(v, mag) : Vector2{ 0.0f, 0.0f };
	}

	float Lerp(float a, float b, float t) {
		return a + (b - a) * t;
	}

	Vector2 EaseOutBack(Vector2 centerPos, Vector2 followerPos, float easeAmount);

	void DrawRound(Obj obj, unsigned int colora) {
		Novice::DrawEllipse(static_cast<int>(obj.pos.x), static_cast<int>(obj.pos.y), static_cast<int>(obj.r.x), static_cast<int>(obj.r.y), obj.angle, colora, kFillModeSolid);
	}

	void DrawCircle(Obj obj, unsigned int colora) {
		Novice::DrawEllipse(static_cast<int>(obj.pos.x), static_cast<int>(obj.pos.y), static_cast<int>(obj.r.x), static_cast<int>(obj.r.y), obj.angle, colora, kFillModeWireFrame);
	}

	void DrawRound(Subobj obj, unsigned int colora) {
		Novice::DrawEllipse(static_cast<int>(obj.pos.x), static_cast<int>(obj.pos.y), static_cast<int>(obj.r.x), static_cast<int>(obj.r.y), obj.angle, colora, kFillModeSolid);
	}

	void DrawCircle(Subobj obj, unsigned int colora) {
		Novice::DrawEllipse(static_cast<int>(obj.pos.x), static_cast<int>(obj.pos.y), static_cast<int>(obj.r.x), static_cast<int>(obj.r.y), obj.angle, colora, kFillModeWireFrame);
	}

	/// <summary>
	/// 楕円運動関数
	/// </summary>
	/// <param name="">構造体</param>
	/// <param name="">回転中心点のX座標</param>
	/// <param name="">回転中心点のY座標</param>
	/// <param name="">回転速度</param>
	/// <returns></returns>
	void FloatingOver(Obj& obj, float x, float y, float flaoting_speed) {

		obj.tilt_rad = obj.tilt / 180.0F * static_cast<float>(M_PI);

		obj.w = obj.timer / 180.0F * static_cast<float>(M_PI);
		obj.pos.x = static_cast<float>(obj.ellipse.x * cosf(obj.w) * cosf(obj.tilt_rad) - obj.ellipse.y * sinf(obj.w) * sinf(obj.tilt_rad) + x);
		obj.pos.y = static_cast<float>(obj.ellipse.x * cosf(obj.w) * sinf(obj.tilt_rad) + obj.ellipse.y * sinf(obj.w) * cosf(obj.tilt_rad) + y);

		//回転
		obj.timer += flaoting_speed;
		if (obj.timer >= 360.0f) {
			obj.timer = 0.0f;
		}
	}

};