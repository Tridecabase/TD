#ifndef BOSS_H
#define BOSS_H

#include <string>
#include <vector>
#include <Novice.h>
#include "Vector2.h"

//行動IDに基づいたBOSS行動モジュール
enum class ActionID {
    MOVE_AND_DEPLOY,      //移動して浮遊砲を設置する行動
    FIRE_AT_PLAYER,       //プレイヤーに向けた弾を多方向に発射
    BREAK_STATE           //ブレイク状態
                          //and more...
};


class Boss {
public:
    // コンストラクタとデストラクタ
    Boss(const std::string& name, int maxHp, int breakMeterMax);
    ~Boss();

    //初期化
    void Init(); 
    //更新
    void Update();
    //描画
    void Render() const;

    //行動をランダムに選択して実行
    void PerformAction();

    //ダメージを受けた際の処理
    void TakeDamage(int damage);

    //ブレイクゲージを更新
    void UpdateBreakMeter();

    //ステータス取得用メソッド
    int GetHP() const { return hp; }
    int GetBreakMeter() const { return break_meter; }
    bool IsInBreakState() const { return is_break; }

private:
    std::string name;               //BOSSの名前
    int hp;                         //現在のHP
    int max_hp;                     //最大HP
    int break_meter;                //ブレイクゲージ
    int break_meter_max;            //ブレイクゲージの最大値
    bool is_break;                  //ブレイク状態フラグ
    int break_timer;                //ブレイク状態の残り時間

    ActionID current_action;        //現在の行動
    int action_timer;               //行動の残り時間

    //行動を切り替える関数
    void SetRandomAction();

    //行動を実行する関数
    void ExecuteMoveAndDeploy();    //ID 101: 移動して浮遊砲を設置
    void ExecuteFireAtPlayer() const;     //ID 102: 弾を多方向に発射

    //ブレイク状態の管理
    void EnterBreakState();         //ブレイク状態に入る
    void ExitBreakState();          //ブレイク状態を終了

    //弾の描画位置
    Vector2 pos;
};

#endif

