#ifndef CONFIG_H
#define CONFIG_H

/*
 * Config.h の使用方法
 *
 * このヘッダファイルは、ゲームの基本的な定数を定義しています。
 *
 * 【使い方】
 * 1. ファイルに `#include "./Tools/config.h"` でインクルードします。
 * 2. 定義された定数は直接使用できます。例: `WINDOW_WIDTH`, `VOLUME_MUSIC`。
 *
 * 【注意】
 * - 定数は変更できないため、動的に変更したい場合は新たな変数を用意してください。
 *
 * このファイルを使うことで、ゲームの基本設定を一元管理できます。
 */
 ////////////////////////////////////////////////////////////////////////////////////////////
 //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ウィンドウ設定↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
 ////////////////////////////////////////////////////////////////////////////////////////////

//ウィンドウのサイズ
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

//math pie
const float M_PI1 = 3.141592f;

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓フレーム設定↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

const float DELTA_TIME = 1.0f / 60.0f;



////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓音量設定↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ゲームステージ設定↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

//最大スクロール数
const int MAX_SCROLL = 3;
//プレイヤーマップブロックのサイズ
const float BLOCK_SIZE = 96.0f;
//外層背景の移動速度
const float OUTER_BG_SPEED = 10.0f;

const int MAX_PARTICLES = 20;


////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓アイテム設定↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓プレイヤー設定↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

//プレイヤーの基準攻撃力
const int MAX_BULLET_A = 32;
const int MAX_BULLET_B = 10;
const int MAX_SHELL_C = 5;
const int MAX_BULLET_C = 15;
const int MAX_BULLET_D = 32;

//プレイヤーの最大HP
const int PlAYER_MAX_HP = 3;

const int PLAYER_ATK = 4;


////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓敵設定↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

//敵の位置
const float ENEMY_SPAWN_POSX = 0.0f;
const float ENEMY_SPAWN_POSY = 100.0f;

//敵の最大HP
const int ENEMY_MAX_HP = 1000;

//敵のHPBAR

//敵の最大浮遊砲数
const int MAX_FUNNEL = 12;
//浮遊砲最大弾数
const int MAX_BULLET_FUNNEL = MAX_FUNNEL;
//奥移動の速度
const float BULLET_VEL_Z = 0.02f;

const int FUNNEL_ATK = 1;

#endif
