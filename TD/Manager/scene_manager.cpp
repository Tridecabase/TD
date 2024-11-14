#include "scene_manager.h"

SceneManager::SceneManager(): current_scene(SceneState::GAMETITLE), stage(new Stage) {

}
SceneManager::~SceneManager() {
    delete stage;
}

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::Init() {

    //初期シーンを設定
    current_scene = SceneState::GAMETITLE;
    //ステージ要素の初期化
    stage->Init();

    is_stage_off = true;

    //test wave
    wave1 = new WaveGenerator(0.0f, 100.0f, WINDOW_WIDTH ,640, 20, 100, 2.0f, 300, 0xffffffff);
    wave2 = new WaveGenerator(0.0f, 300.0f, WINDOW_WIDTH, 1280, 20, 100, 2.0f, 300, 0xffffffff);
    wave3 = new WaveGenerator(0.0f, 500.0f, WINDOW_WIDTH, 640, 30, 200, 4.0f, 200, 0xffffffff);
}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::Update(char keys[256], char preKeys[256]) {

    switch (current_scene) {
    case SceneState::GAMETITLE:

        //テスト用シーン切り替え
        if (keys[DIK_M] && !preKeys[DIK_M]) {
            current_scene = SceneState::LOADING;
        }
        //テスト用シーン切り替え

        break;
    case SceneState::LOADING:

        //ステージ要素の再初期化
        stage->Init();

        //test wave
        wave1->WaveUpdate();
        wave2->WaveRandomUpdate();
        wave3->WaveNoiseUpdate();

        //テスト用シーン切り替え
        if (keys[DIK_M] && !preKeys[DIK_M]) {
            current_scene = SceneState::GAMESTART;
        }
        //テスト用シーン切り替え

        break;
    case SceneState::GAMESTART:

        //ステージ要素の更新処理
        stage->Update(keys,preKeys);
        if (is_stage_off) {
            is_stage_off = false;
        }


        //テスト用シーン切り替え
        if (keys[DIK_M] && !preKeys[DIK_M]) {
            current_scene = SceneState::GAMEEND;
        }
        //テスト用シーン切り替え

        break;
    case SceneState::GAMEEND:

        if (is_stage_off) {
            stage->~Stage();
            is_stage_off = false;
        }

        //テスト用シーン切り替え
        if (keys[DIK_M] && !preKeys[DIK_M]) {
            current_scene = SceneState::GAMETITLE;
        }
        //テスト用シーン切り替え

        break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::Render() {


    switch (current_scene) {
    case SceneState::GAMETITLE:

        //テスト用背景
        Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x708090ff, kFillModeSolid);
        //テスト用シーン切り替え
        Novice::ScreenPrintf(10, 30, "current_scene : GAMETITLE");

        break;
    case SceneState::LOADING:

        //テスト用背景
        Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x6495edff, kFillModeSolid);
        //テスト用シーン切り替え
        Novice::ScreenPrintf(10, 30, "current_scene : LOADING");

        //test wave
        wave1->Render();
        wave2->Render();
        wave3->Render();

        break;
    case SceneState::GAMESTART:

        //テスト用背景
        Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x808080ff, kFillModeSolid);
        //テスト用シーン切り替え
        Novice::ScreenPrintf(10, 30, "current_scene : GAMESTART");

        stage->Render();


        break;
    case SceneState::GAMEEND:

        //テスト用背景
        Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x20b2aaff, kFillModeSolid);
        //テスト用シーン切り替え
        Novice::ScreenPrintf(10, 30, "current_scene : GAMEEND");

        break;
    }

    //テスト用シーン切り替えボータン
    Novice::ScreenPrintf(10,10,"press M to change scene");
}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////


void SceneManager::ChangeScene(SceneState newScene) {
    current_scene = newScene;
}