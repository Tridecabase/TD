#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Vector2.h"
#include <string>
#include <map>
#include "./Tools/csv_parser.h"
#include "./Tools/config.h"
#include "./Tools/wave_generator.h"
#include "./Scene/title.h"
#include "./Scene/stage.h"
#include "./Scene/TestStage.h"
#include "stageClear.h"
#include "gameOver.h"
#include "./Manager/resource_manager.h"


class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    //シーンの初期化
    void Init();
    //シーンの更新
    void Update(char keys[256], char preKeys[256]);
    //シーンの描画
    void Render();


    ////////////////////////////////////////////////////////////////////////////////////////////
    //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓scenemanager.cppで使用するための変数をここで宣言↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
    ////////////////////////////////////////////////////////////////////////////////////////////

private:

    //シーンの状態を表す列挙型
    enum class SceneState {
        GAMETITLE,
        GAMESTART,
        GAMECLEAR,
        GAMEOVER,
        GAMETEST
    };

    void ChangeScene(SceneState newScene);

    //resource_managerの関数を使えるため
    ResourceManager resourceManager;
    //現在のシーン
    SceneState current_scene;
    //現在のステージ
    Title* title;
    Stage* stage;
    TestStage* testStage;
    GameOver* gameOver;
    StageClear* stageClear;


    bool is_stage_off;

    //title bgm
    int playHandle;
    int title_hanlde;
    bool is_title_played;

    //stage bgm
    int stage_hanlde;
    bool is_stage_played;

    //clear bgm
    int clear_hanlde;
    bool is_clear_played;

    float volume;

    //player se
    int death_hanlde;

};
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑scenemanager.cppで使用するための変数をここで宣言↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

#endif