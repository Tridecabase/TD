#pragma once

#pragma once
#include <Novice.h>
#include <Vector2.h>
#include <time.h>
#include "./Tools/config.h"
#include "./Entities/obj.h"
#include "./Characters/player.h"
#include "drawPolygon.h"
#include "effect.h"
#include "UI.h"
#include "./Characters/enemy.h"
#include "./Tools/config.h"

class gameOver
{
public:
	gameOver();
	~gameOver();
	///�����o�[�֐�

	//�^�C�g���̏���������
	void Init();
	//�^�C�g���̍X�V����
	void Update();
	//�^�C�g���̕`�揈��
	void Render();

	///�����o�[�ϐ�
	int randNumber;

	UI* ui;

	Obj* window[4];
	int openClock;
	int openTime;

	int aniClock;
	int aniTime;

	int scClock;
	int scTime;
	bool scFlat;

	int yMoveNum[6];
	int changeNum[6];
	int changeClockClock[6];
	int changeClockTime[6];

	RuningBinary* runingBinary;

	Player* player;

	//�G�̐錾
	Enemy* enemy;
};

