#include "stage.h"

//コンストラクタ
Stage::Stage()
	: background(nullptr), map(nullptr), ui(nullptr), player(nullptr),bullet(nullptr), bulletA(nullptr), bulletB(nullptr), bulletC(nullptr),bulletD(nullptr), funnelBullet(nullptr), droneBullet(nullptr), enemy(nullptr) {

	openTime = 60;
	openClock = openTime;
	aniClock = 0;
	aniTime = 60;
	scClock = 0;
	scTime = 60;
	scFlat = 0;

	Init();
}

// デストラクタ
Stage::~Stage() {
	delete background;
	delete player;
	delete bullet;
	delete bulletA;
	delete bulletB;
	delete bulletC;
	delete bulletD;
	delete funnelBullet;
	delete droneBullet;
	delete map;
	delete enemy;
	delete ui;

	background = nullptr;
	player = nullptr;
	bullet = nullptr;
	bulletA = nullptr;
	bulletB = nullptr;
	bulletC = nullptr;
	bulletD = nullptr;
	funnelBullet = nullptr;
	droneBullet = nullptr;
	map = nullptr;
	enemy = nullptr;
	ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓初期化はここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Init() {
	if (background) { delete background; background = nullptr; }
	if (player) { delete player; player = nullptr; }
	if (bullet) { delete bullet; bullet = nullptr; }
	if (bulletA) { delete bulletA; bulletA = nullptr; }
	if (bulletB) { delete bulletB; bulletB = nullptr; }
	if (bulletC) { delete bulletC; bulletC = nullptr; }
	if (bulletD) { delete bulletD; bulletD = nullptr; }
	if (funnelBullet) { delete funnelBullet; funnelBullet = nullptr; }
	if (droneBullet) { delete droneBullet; droneBullet = nullptr; }
	if (map) { delete map; map = nullptr; }
	if (enemy) { delete enemy; enemy = nullptr; }
	if (ui) { delete ui; ui = nullptr; }

	background = new Background;
	player = new Player;
	bullet = new Bullet;
	bulletA = new BulletA;
	bulletB = new BulletB;
	bulletC = new BulletC;
	bulletD = new BulletD;
	funnelBullet = new FunnelBullet;
	droneBullet = new DroneBullet;
	map = new Map;
	enemy = new Enemy;
	ui = new UI;

	background->Init();
	player->Init(map);
	bullet->Init();
	bulletA->Init();
	bulletB->Init();
	bulletC->Init();
	bulletD->Init();
	funnelBullet->init();
	droneBullet->init();
	enemy->Init();

	openTime = 60;
	openClock = openTime;
	aniClock = 0;
	aniTime = 60;
	scClock = 0;
	scTime = 60;
	scFlat = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑初期化はここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓更新処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Update(char keys[256], char preKeys[256]) {
    if (background) {
        //背景の更新処理
        background->Update(player, map, keys);
    }

    if (player) {
        //プレイヤーの移動処理
        player->Move(map, keys, preKeys);
    }

    //プレイヤー弾丸の更新処理
    if (bullet) {
        bullet->Update();
    }
    if (bulletA) {
        bulletA->Shot(player, bullet);
        bulletA->Scroll(player, keys);
    }
    if (bulletB) {
        bulletB->Shot(player, bullet);
        bulletB->Scroll(player, keys);
    }
    if (bulletC) {
        bulletC->Shot(player, bullet);
        bulletC->Scroll(player, keys);
    }
    if (bulletD) {
        bulletD->Shot(player, bullet);
        bulletD->Scroll(player, keys);
    }

    //敵の更新処理
    if (enemy) {
        enemy->Move(player, bulletA, bulletB, bulletD);
        enemy->Scroll(player, keys);
        enemy->UpdateFunnel(player, bulletA, bulletB, bulletC, bulletD);
    }

    //敵弾丸の更新処理
    if (funnelBullet) {
        funnelBullet->Shot(player, enemy);
        funnelBullet->Scroll(player, keys);
    }
    if (droneBullet) {
        droneBullet->Shot(player, enemy);
        droneBullet->Scroll(player, keys);
    }

    //UI処理
    if (ui) {
        ui->Updata();
    }

    //opening時計
    if (openClock > 0) {
        openClock--;
    }

    //aniClock
    if (aniClock != aniTime) {
        aniClock++;
    } else {
        aniClock = 0;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑更新処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓描画処理ここから↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Render() {
    if (background) {
        //背景の描画
        background->Render(player);
    }

    if (enemy) {
        //敵のUI描画
        enemy->DrawInfo();
        enemy->DrawFunnel();
        //敵の描画
        enemy->Draw(int(player->screen_pos.x), int(player->screen_pos.y));
    }

    if (funnelBullet) {
        funnelBullet->Draw();
    }
    if (droneBullet) {
        droneBullet->Draw();
    }

    //プレイヤー弾丸の描画
    if (bulletA) { bulletA->Draw(); }
    if (bulletB) { bulletB->Draw(); }
    if (bulletC) { bulletC->Draw(); }
    if (bulletD) { bulletD->Draw(); }

    if (player) {
        //プレイヤーの描画
        player->Draw(player->color1, TRUE);
    }

    if (ui) {
        //UIの描画
        ui->Draw();
    }

    if (openClock > 0) {
        stageChangeShow(openClock, openTime, 0x4BBC54FF, 1);
    }

    if (scFlat) {
        stageChangeShow(scClock, scTime, 0x4BBC54FF, 0);
    }

    Novice::ScreenPrintf(10, 700, "%d /%d", aniClock, aniTime);
}


bool Stage::StageChanger(char key[256],char preKey[256])
{
	if (key[DIK_M] && !preKey[DIK_M]) {
		if (!scFlat) {
			scFlat = 1;
			scClock = scTime;
		}
	}
	if (scClock != 0) {
		scClock--;
	} else {
		if (scFlat > 0) {
			return true;
		}
	}
	return false;
}
;
////////////////////////////////////////////////////////////////////////////////////////////
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑描画処理ここまで↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑//
////////////////////////////////////////////////////////////////////////////////////////////