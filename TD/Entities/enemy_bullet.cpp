#include "enemy_bullet.h"

FunnelBullet::FunnelBullet() {
	init();
}
FunnelBullet::~FunnelBullet() {
	if (particle) {
		delete particle;
		particle = nullptr;
	}
}

void FunnelBullet::init() {

	particle = new ParticleGenerator();

	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		funnelBullet[i] = {
		{0.0f,0.0f,1.0f},	//pos
		{0.0f,0.0f},		//pos
		{0.0f,0.0f},		//target pos
		0.0f,	//gravityY 
		0.0f,	//gravitySpeedY
		30.0f,	//radius 
		1.0f,	//scale 
		3.0f,	//speed
		0.0f,	//angle
		150.0f,	//time
		200,	//cooldown
		0.0f,	//distanceToMouse
		0.0f,	//altitude
		0.0f,	//frontAltitude
		false	//isShoot 
		};
	}

}

void FunnelBullet::Shot(Player* player, Enemy* enemy) {
	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (enemy->funnel[i].isActive) {
			funnelBullet[i].cooldown--;
		}


		funnelBullet[i].angle += 0.1f;
		if (funnelBullet[i].angle >= 2 * static_cast<float>(M_PI)) {
			funnelBullet[i].angle -= 2 * static_cast<float>(M_PI);
		}

		if (funnelBullet[i].cooldown <= 0 && !funnelBullet[i].isShoot) {
			funnelBullet[i].cooldown = 150;


			funnelBullet[i].pos.x = enemy->funnel[i].x;
			funnelBullet[i].pos.y = enemy->funnel[i].y;
			funnelBullet[i].pos.z = 1.0f;


			funnelBullet[i].target_pos.x = player->screen_pos.x;
			funnelBullet[i].target_pos.y = player->screen_pos.y;


			float dirX = funnelBullet[i].target_pos.x - funnelBullet[i].pos.x;
			float dirY = funnelBullet[i].target_pos.y - funnelBullet[i].pos.y;

            if (- dirX > static_cast<float>(WINDOW_WIDTH * MAX_SCROLL / 2.0f)) {
                funnelBullet[i].pos.x -= WINDOW_WIDTH * MAX_SCROLL;
            }

			float magnitude = sqrtf(dirX * dirX + dirY * dirY);

			funnelBullet[i].time = magnitude / funnelBullet[i].speed;
			funnelBullet[i].velocity.x = dirX / funnelBullet[i].time;
			funnelBullet[i].velocity.y = dirY / funnelBullet[i].time;

			funnelBullet[i].isShoot = true;
		}
	}


	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (funnelBullet[i].isShoot) {

			funnelBullet[i].pos.x += funnelBullet[i].velocity.x;
			funnelBullet[i].pos.y += funnelBullet[i].velocity.y;

			float dirX = funnelBullet[i].target_pos.x - funnelBullet[i].pos.x;
			float dirY = funnelBullet[i].target_pos.y - funnelBullet[i].pos.y;
			float magnitude = sqrtf(dirX * dirX + dirY * dirY);


            if (- dirX > static_cast<float>(WINDOW_WIDTH * MAX_SCROLL / 2.0f)) {
                funnelBullet[i].pos.x -= WINDOW_WIDTH * MAX_SCROLL;
            }

			funnelBullet[i].time = magnitude / funnelBullet[i].speed;
			funnelBullet[i].velocity.x = dirX / funnelBullet[i].time;
			funnelBullet[i].velocity.y = dirY / funnelBullet[i].time;

			funnelBullet[i].pos.z = 1.0f - (funnelBullet[i].pos.y - enemy->funnel[i].y) / (530.0f - enemy->funnel[i].y);
			funnelBullet[i].pos.z = max(0.0f, funnelBullet[i].pos.z);
			funnelBullet[i].scale = 0.2f + 0.8f * (1.0f - funnelBullet[i].pos.z);
			if (particle) {
				particle->GenerateParticles(
					funnelBullet[i].pos.x,
					funnelBullet[i].pos.y,
					0x4BBC5444
				);
			}
			float dx = funnelBullet[i].pos.x - funnelBullet[i].target_pos.x;
			float dy = funnelBullet[i].pos.y - funnelBullet[i].target_pos.y;
			if (sqrtf(dx * dx + dy * dy) < 32.0f) {
				if (particle) {
					particle->Destroy(
						funnelBullet[i].pos.x,
						funnelBullet[i].pos.y,
						0x4BBC5444
					);
				}
				funnelBullet[i].isShoot = false;
			}
		}
	}

	//当たり判定
	for (int i = 0; i < MAX_BULLET_FUNNEL; i++) {
		if (funnelBullet[i].isShoot) {
			if (player->screen_pos.x + player->width / 2 >= funnelBullet[i].pos.x - funnelBullet[i].radius * funnelBullet[i].scale &&
				player->screen_pos.x - player->width / 2 <= funnelBullet[i].pos.x + funnelBullet[i].radius * funnelBullet[i].scale) {
				if (player->screen_pos.y + player->height / 2 >= funnelBullet[i].pos.y - funnelBullet[i].radius * funnelBullet[i].scale &&
					player->screen_pos.y - player->height / 2 <= funnelBullet[i].pos.y + funnelBullet[i].radius * funnelBullet[i].scale) {
					if (!player->isHit) {
						particle->Destroy(
							funnelBullet[i].pos.x,
							funnelBullet[i].pos.y,
							0xFF000044
						);
						player->isHit = true;
						player->hp -= FUNNEL_ATK;
					}
					funnelBullet[i].isShoot = false;
				}
			}
		}
	}
}

void FunnelBullet::Scroll(Player* player, char keys[256]) {
	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		if (funnelBullet[i].isShoot) {

			float dx = funnelBullet[i].pos.x - player->screen_pos.x;
			float dy = funnelBullet[i].pos.y - player->screen_pos.y;
			float dz = funnelBullet[i].pos.z;

			float theta = atan2(dy, dx);

			float scrollFactor = OUTER_BG_SPEED * dz * sin(theta);

			if (funnelBullet[i].pos.y < 530.0f) {
				if (player->isPlayerLeft && keys[DIK_A]) {
					funnelBullet[i].pos.x -= scrollFactor;
				}
				if (player->isPlayerRight && keys[DIK_D]) {
					funnelBullet[i].pos.x += scrollFactor;
				}
			}
		}
	}
}

//描画処理
void FunnelBullet::Draw() {

	if (particle) {
		particle->Render();
	}

    //敵弾の照準表現
    for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
        if (funnelBullet[i].isShoot) {
            unsigned int line_color{};
            if (funnelBullet[i].pos.z >= 0.2f) {
                line_color = 0x4BBC5422;
            }
            if (funnelBullet[i].pos.z <= 0.2f) {
                line_color = RED;
            }

            //線
            Novice::DrawLine(
                static_cast<int>(funnelBullet[i].pos.x),
                static_cast<int>(funnelBullet[i].pos.y),
                static_cast<int>(funnelBullet[i].target_pos.x),
                static_cast<int>(funnelBullet[i].target_pos.y),
                line_color
            );
            //円
            Novice::DrawEllipse(
                static_cast<int>(funnelBullet[i].target_pos.x),
                static_cast<int>(funnelBullet[i].target_pos.y),
                10, 5, 0.0f, line_color, kFillModeSolid);
        }
    }
 

	for (int i = 0; i < MAX_BULLET_FUNNEL; ++i) {
		float posX = funnelBullet[i].pos.x; //現在のX座標
		float posY = funnelBullet[i].pos.y; //現在のY座標
		float radius = funnelBullet[i].radius * funnelBullet[i].scale; //半径

		float angleOffset = funnelBullet[i].angle; //角度オフセット

		float outerPoints[5][2]{}; //starの点

		//点を計算
		for (int j = 0; j < 5; ++j) {
			//点の計算
			float outerAngle = angleOffset + j * (2 * static_cast<float>(M_PI) / 5);
			outerPoints[j][0] = posX + cos(outerAngle) * radius;
			outerPoints[j][1] = posY + sin(outerAngle) * radius;
		}

		if (funnelBullet[i].isShoot) {
			//外部線を描画
			for (int j = 0; j < 5; ++j) {
				int next = (j + 2) % 5; //次の点を選択

				//線を描画
				Novice::DrawLine(
					static_cast<int>(outerPoints[j][0]),
					static_cast<int>(outerPoints[j][1]),
					static_cast<int>(outerPoints[next][0]),
					static_cast<int>(outerPoints[next][1]),
					0x191B19FF
				);
			}

			//三角形を描画
			for (int j = 0; j < 5; ++j) {
				int next = (j + 2) % 5;

				Novice::DrawTriangle(
					static_cast<int>(outerPoints[j][0]),
					static_cast<int>(outerPoints[j][1]),
					static_cast<int>(outerPoints[next][0]),
					static_cast<int>(outerPoints[next][1]),
					static_cast<int>(posX),
					static_cast<int>(posY),
                    0xf6e16bFF,
					kFillModeSolid
				);
			}
		}
	}
}


DroneBullet::DroneBullet() {
	init();
}

DroneBullet::~DroneBullet() {
	if (particle) {
		delete particle;
		particle = nullptr;
	}
}

void DroneBullet::init() {
    particle = new ParticleGenerator();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX_BULLET_DRONE; ++j) {
            droneBullets[i][j] = {
                {0.0f, 0.0f, 1.0f},  // pos
                {0.0f, 0.0f},       // velocity
                {0.0f, 0.0f},        // target_pos
                25.0f,               // radius
                1.0f,                // scale
                4.0f,                // speed
                0.0f,                // angle
                30.0f,
                100,                 // cooldown
                false                // isShoot
            };
        }
    }
}

void DroneBullet::Shot(Player* player, Enemy* enemy) {
    for (int i = 0; i < 3; ++i) {
        Vector3 dronePos;
        switch (i) {
        case 0:
            dronePos = { enemy->drone1.pos.x, enemy->drone1.pos.y, 1.0f };
            break;
        case 1:
            dronePos = { enemy->drone2.pos.x, enemy->drone2.pos.y, 1.0f };
            break;
        case 2:
            dronePos = { enemy->drone3.pos.x, enemy->drone3.pos.y, 1.0f };
            break;
        default:
            continue;
        }


        for (int j = 0; j < MAX_BULLET_DRONE; ++j) {
            droneBullets[i][j].cooldown--; 

            if (enemy->current_action == ActionID::Figure_Eight) {
                if (droneBullets[i][j].cooldown <= 0 && !droneBullets[i][j].isShoot) {
                    droneBullets[i][j].cooldown = 150;

                    droneBullets[i][j].pos = dronePos;

                    droneBullets[i][j].target_pos.x = player->screen_pos.x;
                    droneBullets[i][j].target_pos.y = player->screen_pos.y;

                    float dirX = droneBullets[i][j].target_pos.x - droneBullets[i][j].pos.x;
                    float dirY = droneBullets[i][j].target_pos.y - droneBullets[i][j].pos.y;
                    float magnitude = sqrtf(dirX * dirX + dirY * dirY);

                    droneBullets[i][j].velocity.x = (dirX / magnitude) * droneBullets[i][j].speed;
                    droneBullets[i][j].velocity.y = (dirY / magnitude) * droneBullets[i][j].speed;

                    droneBullets[i][j].isShoot = true;
                }
            }

            if (enemy->current_action == ActionID::FIRE_AT_PLAYER && enemy->action_timer <= 300) {

                if (droneBullets[i][j].cooldown <= 0 && !droneBullets[i][j].isShoot) {
                    droneBullets[i][j].cooldown = 10;
                    droneBullets[i][j].pos = dronePos;

                    droneBullets[i][j].target_pos.x = player->screen_pos.x;
                    droneBullets[i][j].target_pos.y = player->screen_pos.y;

                    float dirX = droneBullets[i][j].target_pos.x - droneBullets[i][j].pos.x;
                    float dirY = droneBullets[i][j].target_pos.y - droneBullets[i][j].pos.y;
                    float magnitude = sqrtf(dirX * dirX + dirY * dirY);

                    droneBullets[i][j].velocity.x = (dirX / magnitude) * droneBullets[i][j].speed;
                    droneBullets[i][j].velocity.y = (dirY / magnitude) * droneBullets[i][j].speed;

                    droneBullets[i][j].isShoot = true;
                }
            }

            droneBullets[i][j].angle += 0.2f;
            if (droneBullets[i][j].angle >= 2 * static_cast<float>(M_PI)) {
                droneBullets[i][j].angle -= 2 * static_cast<float>(M_PI);
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX_BULLET_DRONE; ++j) {
            if (droneBullets[i][j].isShoot) {
                droneBullets[i][j].pos.x += droneBullets[i][j].velocity.x;
                droneBullets[i][j].pos.y += droneBullets[i][j].velocity.y;

                float dirX = droneBullets[i][j].target_pos.x - droneBullets[i][j].pos.x;
                float dirY = droneBullets[i][j].target_pos.y - droneBullets[i][j].pos.y;
                float magnitude = sqrtf(dirX * dirX + dirY * dirY);


                if (-dirX > static_cast<float>(WINDOW_WIDTH * MAX_SCROLL / 2.0f)) {
                    droneBullets[i][j].pos.x -= WINDOW_WIDTH * MAX_SCROLL;
                }

                droneBullets[i][j].time = magnitude / droneBullets[i][j].speed;
                droneBullets[i][j].velocity.x = dirX / droneBullets[i][j].time;
                droneBullets[i][j].velocity.y = dirY / droneBullets[i][j].time;
                //if (particle) {
                //    particle->GenerateParticles(
                //        droneBullets[i][j].pos.x,
                //        droneBullets[i][j].pos.y,
                //        0x4BBC5444
                //    );
                //}

                float dx = droneBullets[i][j].pos.x - droneBullets[i][j].target_pos.x;
                float dy = droneBullets[i][j].pos.y - droneBullets[i][j].target_pos.y;
                if (sqrtf(dx * dx + dy * dy) < 32.0f) {
                    if (particle) {
                        particle->Destroy(
                            droneBullets[i][j].pos.x,
                            droneBullets[i][j].pos.y,
                            0x4BBC5444
                        );
                    }
                    droneBullets[i][j].isShoot = false;
                }
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX_BULLET_DRONE; ++j) {
            if (droneBullets[i][j].isShoot) {
                if (player->screen_pos.x + player->width / 2 >= droneBullets[i][j].pos.x - droneBullets[i][j].radius * droneBullets[i][j].scale &&
                    player->screen_pos.x - player->width / 2 <= droneBullets[i][j].pos.x + droneBullets[i][j].radius * droneBullets[i][j].scale) {
                    if (player->screen_pos.y + player->height / 2 >= droneBullets[i][j].pos.y - droneBullets[i][j].radius * droneBullets[i][j].scale &&
                        player->screen_pos.y - player->height / 2 <= droneBullets[i][j].pos.y + droneBullets[i][j].radius * droneBullets[i][j].scale) {
                        if (!player->isHit) {
                            player->hp -= FUNNEL_ATK;
                            particle->Destroy(
                                droneBullets[i][j].pos.x,
                                droneBullets[i][j].pos.y,
                                0xFF000044
                            );
                            player->isHit = true;
                        }
                        droneBullets[i][j].isShoot = false;
                    }
                }
            }
        }
    }
}

void DroneBullet::Scroll(Player* player, char keys[256]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX_BULLET_DRONE; ++j) {
            if (droneBullets[i][j].isShoot) {
                float dx = droneBullets[i][j].pos.x - player->screen_pos.x;
                float dy = droneBullets[i][j].pos.y - player->screen_pos.y;
                float dz = droneBullets[i][j].pos.z;

                float theta = atan2(dy, dx);
                float scrollFactor = OUTER_BG_SPEED * dz * sin(theta);

                if (droneBullets[i][j].pos.y < 530.0f) {
                    if (player->isPlayerLeft && keys[DIK_A]) {
                        droneBullets[i][j].pos.x -= scrollFactor;
                    }
                    if (player->isPlayerRight && keys[DIK_D]) {
                        droneBullets[i][j].pos.x += scrollFactor;
                    }
                }
            }
        }
    }
}

void DroneBullet::Draw() {
    if (particle) {
        particle->Render();
    }

    //敵弾の照準表現
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX_BULLET_DRONE; ++j) {
            if (droneBullets[i][j].isShoot) {
                unsigned int line_color{};
                if (droneBullets[i][j].pos.z >= 0.2f) {
                    line_color = 0x4BBC5411;
                }
                if (droneBullets[i][j].pos.z <= 0.2f) {
                    line_color = RED;
                }
                //線
                Novice::DrawLine(
                    static_cast<int>(droneBullets[i][j].pos.x),
                    static_cast<int>(droneBullets[i][j].pos.y),
                    static_cast<int>(droneBullets[i][j].target_pos.x),
                    static_cast<int>(droneBullets[i][j].target_pos.y),
                    line_color
                );
                //円
                Novice::DrawEllipse(
                    static_cast<int>(droneBullets[i][j].target_pos.x),
                    static_cast<int>(droneBullets[i][j].target_pos.y),
                    10, 5, 0.0f, line_color,kFillModeSolid);
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX_BULLET_DRONE; ++j) {
            if (droneBullets[i][j].isShoot) {
                float posX = droneBullets[i][j].pos.x;
                float posY = droneBullets[i][j].pos.y;
                float radius = droneBullets[i][j].radius * droneBullets[i][j].scale;
                float angleOffset = droneBullets[i][j].angle;

                float outerPoints[5][2] = {};

                for (int k = 0; k < 5; ++k) {
                    float outerAngle = angleOffset + k * (2 * static_cast<float>(M_PI) / 5);
                    outerPoints[k][0] = posX + cos(outerAngle) * radius;
                    outerPoints[k][1] = posY + sin(outerAngle) * radius;
                }

                for (int k = 0; k < 5; ++k) {
                    int next = (k + 2) % 5;
                    Novice::DrawLine(
                        static_cast<int>(outerPoints[k][0]),
                        static_cast<int>(outerPoints[k][1]),
                        static_cast<int>(outerPoints[next][0]),
                        static_cast<int>(outerPoints[next][1]),
                        0x191B19FF
                    );
                }

                for (int k = 0; k < 5; ++k) {
                    int next = (k + 2) % 5;
                    Novice::DrawTriangle(
                        static_cast<int>(outerPoints[k][0]),
                        static_cast<int>(outerPoints[k][1]),
                        static_cast<int>(outerPoints[next][0]),
                        static_cast<int>(outerPoints[next][1]),
                        static_cast<int>(posX),
                        static_cast<int>(posY),
                        0xf6e16bFF,
                        kFillModeSolid
                    );
                }
            }
        }
    }
}