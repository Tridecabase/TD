#include "scene_manager.h"

SceneManager::SceneManager() : current_scene(SceneState::GAMETITLE),stage(new Stage),testStage(new TestStage),gameOver(new GameOver),stageClear(new StageClear), title(new Title) {

}
SceneManager::~SceneManager() {
	delete title;
	delete stage;
	delete testStage;
	delete gameOver;
	delete stageClear;
}

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////

void SceneManager::Init() {

	//初期シーンを設定
	current_scene = SceneState::GAMETITLE;
	//ステージ要素の初期化
	title->Init();
	stage->Init();
	testStage->Init();
	gameOver->Init();
	stageClear->Init();

	is_stage_off = true;

	//title bgm
	playHandle = -1;
	title_hanlde = Novice::LoadAudio("../Resources/Sounds/bgm/title.wav");
	is_title_played = false;

	//stage bgm
	stage_hanlde = Novice::LoadAudio("../Resources/Sounds/bgm/stage.mp3");
	is_stage_played = false;

	//clear bgm
	clear_hanlde = Novice::LoadAudio("../Resources/Sounds/bgm/clear.mp3");
	is_stage_played = false;

	volume = 1.0f;

	death_hanlde = Novice::LoadAudio("../Resources/Sounds/effects/player_death.wav");

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
		//Title要素の更新処理
		title->Update();

		/////////////////////////////BGM
		if (!is_title_played) {
			if (!Novice::IsPlayingAudio(playHandle) || playHandle == -1) {
				playHandle = Novice::PlayAudio(title_hanlde, 1, volume);
			}
			is_title_played = true;
		}

		/////テスト用シーンへ切り替え
		//if (keys[DIK_T] && !preKeys[DIK_T]) {
		//    current_scene = SceneState::GAMETEST;
		//	testStage->Init();
		//}
		if (title->StageChanger()) {
			//if (!Novice::IsPlayingAudio(playHandle) || playHandle == -1) {
			//	playHandle = Novice::PlayAudio(click_handle, 0, 1.0f);
			//}
			is_title_played = false;
			Novice::StopAudio(playHandle);
			stage->Init();
			current_scene = SceneState::GAMESTART;
		}
		//テスト用シーン切り替え

		break;
	case SceneState::GAMESTART:

		//ステージ要素の更新処理
		stage->Update(keys, preKeys);
		if (is_stage_off) {
			is_stage_off = false;
		}

		/////////////////////////////BGM
		if (!is_stage_played) {
			if (!Novice::IsPlayingAudio(playHandle) || playHandle == -1) {
				playHandle = Novice::PlayAudio(stage_hanlde, 1, 0.7f);
			}
			is_stage_played = true;
		}


		////テスト用シーン切り替え
		//if (keys[DIK_O] && !preKeys[DIK_O]) {
		//	stage->player->hp = 0;
		//   
		//}
		//if (keys[DIK_M] && !preKeys[DIK_M]) {
		//	is_stage_played = false;
		//	Novice::StopAudio(playHandle);
		//	stage->enemy->current_action = ActionID::ENEMY_DEATH;
		//	stage->enemy->action_timer = 480;
		//}
		

		//敵を倒したらシーン切り替え
		if (stage->enemy->death_flag == true) {
			is_stage_played = false;
			Novice::StopAudio(playHandle);
			current_scene = SceneState::GAMECLEAR;
			stageClear->Init();
			stage->Init();
		}
		
		//プレイヤーが倒されたらシーン切り替え
		if (stage->player->hp <= 0) {
			is_stage_played = false;
			Novice::StopAudio(playHandle);
			/////////////////////////////SE
			if (!Novice::IsPlayingAudio(playHandle) || playHandle == -1) {
				playHandle = Novice::PlayAudio(death_hanlde, 0, 1.0f);
			}

			current_scene = SceneState::GAMEOVER;
			gameOver->Init();
			stage->Init();
		}

		break;
	case SceneState::GAMECLEAR:

		stageClear->Update();

		if (is_stage_off) {
			is_stage_off = false;
		}

		/////////////////////////////BGM
		if (!is_clear_played) {
			if (!Novice::IsPlayingAudio(playHandle) || playHandle == -1) {
				playHandle = Novice::PlayAudio(clear_hanlde, 1, volume);
			}
			is_clear_played = true;
		}

		//テスト用シーン切り替え
		if (keys[DIK_M] && !preKeys[DIK_M]) {
			is_clear_played = false;
			Novice::StopAudio(playHandle);
			current_scene = SceneState::GAMETITLE;
			title->Init();
			stage->Init();
		}
		

		break;
	case SceneState::GAMEOVER:

		gameOver->Update();

		if (is_stage_off) {
			is_stage_off = false;
		}

		//テスト用シーン切り替え
		if (keys[DIK_M] && !preKeys[DIK_M]) {
			current_scene = SceneState::GAMETITLE;
			title->Init();
			stage->Init();
		}
		

		break;
	case SceneState::GAMETEST:


		testStage->Update();

		//テスト用シーン切り替え
		if (keys[DIK_T] && !preKeys[DIK_T]) {
			current_scene = SceneState::GAMETITLE;
			title->Init();
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
		//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x708090ff, kFillModeSolid);
		//テスト用シーン切り替え
		//Novice::ScreenPrintf(10, 30, "current_scene : GAMETITLE");

		title->Render();

		break;
	case SceneState::GAMESTART:

		//テスト用背景
		//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x808080ff, kFillModeSolid);
		//テスト用シーン切り替え
		//Novice::ScreenPrintf(10, 30, "current_scene : GAMESTART");

		stage->Render();


		break;
	case SceneState::GAMECLEAR:

		////テスト用背景
		//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x20b2aaff, kFillModeSolid);
		////テスト用シーン切り替え
		//Novice::ScreenPrintf(10, 30, "current_scene : GAMEEND");
		stageClear->Render();

		break;
	case SceneState::GAMEOVER:

		//テスト用背景
		//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x20b2aaff, kFillModeSolid);
		//テスト用シーン切り替え
		//Novice::ScreenPrintf(10, 30, "current_scene : GAMEEND");

		gameOver->Render();

		break;
	case SceneState::GAMETEST:

		//テスト用背景
		//Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0x20b2aaff, kFillModeSolid);
		//テスト用シーン切り替え
		Novice::ScreenPrintf(10, 30, "current_scene : GAMEEND");

		testStage->Render();

		break;
	}

	//テスト用シーン切り替えボータン
	//if (current_scene != SceneState::GAMETITLE) {
	//	if (current_scene != SceneState::GAMEOVER) {
	//		Novice::ScreenPrintf(10, 10, "press M to change scene");
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////


void SceneManager::ChangeScene(SceneState newScene) {
	current_scene = newScene;
}