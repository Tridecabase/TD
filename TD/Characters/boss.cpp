#include "Boss.h"
#include <Novice.h>
#include <random>

//コンストラクタ
Boss::Boss(const std::string& name, int maxHp, int breakMeterMax)
    : name(name), hp(maxHp), max_hp(maxHp), break_meter(breakMeterMax),
    break_meter_max(breakMeterMax), is_break(false), break_timer(0),
    action_timer(0), current_action(ActionID::MOVE_AND_DEPLOY), pos(Vector2(0, 0)) {
}

//デストラクタ
Boss::~Boss() {}

//BOSSの初期化
void Boss::Init() {
    hp = max_hp;
    break_meter = break_meter_max;
    is_break = false;
    break_timer = 0;
    SetRandomAction();
}

//BOSSの更新
void Boss::Update() {
    //ブレイク状態の場合、ブレイクタイマーを減らす
    if (is_break) {
        break_timer--;
        if (break_timer <= 0) {
            ExitBreakState();
        }
    }
    else {
        // 通常状態で行動モジュールを実行
        if (action_timer <= 0) {
            SetRandomAction();
        }
        PerformAction();
        action_timer--;
    }

    // ブレイクゲージの回復
    UpdateBreakMeter();
}

//BOSSの描画
void Boss::Render() const {
    Novice::DrawBox(static_cast<int>(pos.x), static_cast<int>(pos.y), 64, 64, 0.0f, 0xFFFFFFFF, kFillModeSolid); //BOSSの位置に正方形を描画
    //HPゲージやブレイクゲージの描画もここに追加可能
}

//行動をランダムに選択して実行
void Boss::PerformAction() {
    switch (current_action) {
    case ActionID::MOVE_AND_DEPLOY:
        ExecuteMoveAndDeploy();
        break;
    case ActionID::FIRE_AT_PLAYER:
        ExecuteFireAtPlayer();
        break;
    case ActionID::BREAK_STATE:
        break; //ブレイク状態中は行動しない
    }
}

//ダメージを受けた際の処理
void Boss::TakeDamage(int damage) {
    hp -= damage;
    break_meter -= damage / 2; //ブレイクメーターはHPダメージの半分減少
    if (break_meter <= 0 && !is_break) {
        EnterBreakState();
    }
}

//ブレイクゲージを更新
void Boss::UpdateBreakMeter() {
    if (!is_break && break_meter < break_meter_max) {
        break_meter++; //徐々にブレイクゲージを回復
    }
}

//行動を切り替え
void Boss::SetRandomAction() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    int actionChoice = dist(gen);
    if (actionChoice == 0) {
        current_action = ActionID::MOVE_AND_DEPLOY;
        action_timer = 100; //行動の持続時間を設定
    }
    else {
        current_action = ActionID::FIRE_AT_PLAYER;
        action_timer = 80; //行動持続時間
    }
}

//行動ID 101
void Boss::ExecuteMoveAndDeploy() {
    pos.x += 5;

    //定期的に浮遊砲を設置
    static int deploy_interval = 30; //浮遊砲の間隔
    if (action_timer % deploy_interval == 0) {
        //Novice::DrawEllipse(pos.x, pos.y + 20, 5, 5, 0.0f, 0xFFFF00FF, kFillModeSolid); //発射した弾の仮描画
    }
}

//行動ID 102
void Boss::ExecuteFireAtPlayer() const {
    static int fire_interval = 20; // 弾の発射間隔
    if (action_timer % fire_interval == 0) {
        // プレイヤーに向けて弾を発射する処理を追加可能
        //Novice::DrawEllipse(pos.x, pos.y - 10, 5,5,0.0f, 0xFFFF00FF, kFillModeSolid); //発射した弾の仮描画
    }
}

//ブレイク状態に入る
void Boss::EnterBreakState() {
    is_break = true;
    break_timer = 300; //ブレイク状態の持続時間（例：300フレーム）
    break_meter = break_meter_max; //ブレイクゲージをリセット
}

//ブレイク状態を終了
void Boss::ExitBreakState() {
    is_break = false;
    SetRandomAction(); //ブレイク終了後、行動を再設定
}
