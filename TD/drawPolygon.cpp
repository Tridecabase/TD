﻿#include "drawPolygon.h"



///////////////////////////////////////////////////////////////Polygon

void DrawPolygon(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4, const int color) {
	Novice::DrawTriangle(int(point1.x), int(point1.y),
		int(point2.x), int(point2.y),
		int(point3.x), int(point3.y),
		color, kFillModeSolid);
	Novice::DrawTriangle(int(point1.x), int(point1.y),
		int(point3.x), int(point3.y),
		int(point4.x), int(point4.y),
		color, kFillModeSolid);
}

void DrawPolygon(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4
	, const Vector2 point5, const int color) {
	Novice::DrawTriangle(int(point1.x), int(point1.y),
		int(point2.x), int(point2.y),
		int(point3.x), int(point3.y),
		color, kFillModeSolid);
	Novice::DrawTriangle(int(point2.x), int(point2.y),
		int(point3.x), int(point3.y),
		int(point4.x), int(point4.y),
		color, kFillModeSolid);
	Novice::DrawTriangle(int(point3.x), int(point3.y),
		int(point4.x), int(point4.y),
		int(point5.x), int(point5.y),
		color, kFillModeSolid);
}

void DrawPolygon(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4
	, const Vector2 point5, const Vector2 point6, const int color) {
	Novice::DrawTriangle(int(point1.x), int(point1.y),
		int(point2.x), int(point2.y),
		int(point3.x), int(point3.y),
		color, kFillModeSolid);
	Novice::DrawTriangle(int(point2.x), int(point2.y),
		int(point3.x), int(point3.y),
		int(point4.x), int(point4.y),
		color, kFillModeSolid);
	Novice::DrawTriangle(int(point3.x), int(point3.y),
		int(point4.x), int(point4.y),
		int(point5.x), int(point5.y),
		color, kFillModeSolid);
	Novice::DrawTriangle(int(point4.x), int(point4.y),
		int(point5.x), int(point5.y),
		int(point6.x), int(point6.y),
		color, kFillModeSolid);
}

void DrawNum(const int posX, const int posY, const int width, const int height, const int color, int Num) {
	float boxSizeX = float(width / 5);
	float boxSizeY = float(height / 7);
	float RTX = float(posX - width / 2);
	float RTY = float(posY - height / 2);

	if (Num == 0) {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else if (Num == 1) {
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 6), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
	}
}
void DrawNum(const int posX, const int posY, const int width, const int color, int Num) {
	int height = int(width * 1.4f);
	float boxSizeX = float(width / 5);
	float boxSizeY = float(height / 7);
	float RTX = float(posX - width / 2);
	float RTY = float(posY - height / 2);

	if (Num == 0) {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else if (Num == 1) {
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 6), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
	}
}

void DrawApla(const int posX, const int posY, const int width, const int color, const char Apla) {

	int height = {};
	float boxSizeX = {};
	float boxSizeY = {};
	if (isupper(Apla)) {
		height = int(width * 1.4f);
		boxSizeX = float(width / 5);
		boxSizeY = float(height / 7);
	}
	if (islower(Apla)) {
		height = int(width * 2.4f);
		boxSizeX = float(width / 3);
		boxSizeY = float(height / 7);
	}
	if (Apla == ':') {
		height = int(width * 2.4f);
		boxSizeX = float(width / 3);
		boxSizeY = float(height / 7);
	}
	float RTX = float(posX - width / 2);
	float RTY = float(posY - height / 2);

	if (Apla == 'A') {
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 4),
			int(boxSizeX * 5), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'B') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'C') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'D') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 2), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 2), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);	
	}else if (Apla == 'G') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'H') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'L') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 6), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 6),
			int(boxSizeX * 4), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'M') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'N') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'O') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'P') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'W') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'Q') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 4), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 4), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'R') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'S') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 1),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);

	}else if (Apla == 'a') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 4), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'b') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'c') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'e') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 2), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == 'g') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'h') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'i') {
			Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
				int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
				int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'k') {
			Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
				int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
				int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
				int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 5),
				int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'l') {
			Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
				int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'm') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 4), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'n') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'o') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'r') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else if (Apla == 's') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else if (Apla == 't') {
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 0),
			int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 6),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'v') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 3), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'u') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 6),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 2),
			int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
	} else if (Apla == 'z') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 4),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 5),
			int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 6),
			int(boxSizeX * 3), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
	}else if (Apla == ':') {
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 1),
			int(boxSizeX * 2), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
		Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 4),
			int(boxSizeX * 2), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
	}else {
		if (isupper(Apla)) {
			Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 0),
				int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 1),
				int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
				int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 3), int(RTY + boxSizeY * 4),
				int(boxSizeX * 1), int(boxSizeY * 2), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 4), int(RTY + boxSizeY * 0),
				int(boxSizeX * 1), int(boxSizeY * 7), 0.0f, color, kFillModeSolid);
		}
		if (islower(Apla)) {
			Novice::DrawBox(int(RTX + boxSizeX * 0), int(RTY + boxSizeY * 2),
				int(boxSizeX * 1), int(boxSizeY * 5), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 1), int(RTY + boxSizeY * 3),
				int(boxSizeX * 1), int(boxSizeY * 1), 0.0f, color, kFillModeSolid);
			Novice::DrawBox(int(RTX + boxSizeX * 2), int(RTY + boxSizeY * 3),
				int(boxSizeX * 1), int(boxSizeY * 4), 0.0f, color, kFillModeSolid);
		}
	}

};


///////////////////////////////////////////////////////////////Line

void DrawLineNew(const Vector2 point1, const Vector2 point2, const int px, int color) {
	for (int i = 0; i < px; i++) {
		if ((point2.x - point1.x) > (point2.y - point1.y)) {
			int a = int(powf(-1.0f, float(i)));
			Novice::DrawLine(int(point1.x + (i / 2)), int(point1.y + a * (i / 2)), int(point2.x + (i / 2)), int(point1.y + a * (i / 2)), color);
		} else {
			int a = int(powf(-1.0f, float(i)));
			Novice::DrawLine(int(point1.x + a * (i / 2)), int(point1.y + (i / 2)), int(point2.x + a * (i / 2)), int(point1.y + (i / 2)), color);
		}
	}
}

///////////////////////////////////////////////////////////////color

int colorChanger(const int color1, const int color2, const int clock, const int time) {
	int changeColor = int((color2 - color1) / float(time));
	return color2 - changeColor * clock;
}

