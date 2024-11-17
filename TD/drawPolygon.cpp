#include "drawPolygon.h"



///////////////////////////////////////////////////////////////Polygon

void DrawPolygon(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4,const int color) {
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
			   , const Vector2 point5, const int color){
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
			   , const Vector2 point5, const Vector2 point6, const int color){
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


///////////////////////////////////////////////////////////////Line

void DrawLineNew(const Vector2 point1, const Vector2 point2, const int px,int color) {
	for (int i = 0; i < px; i++) {
		if ((point2.x - point1.x) > (point2.y - point1.y)) {
			int a = int(powf(-1.0f, float(i)));
			Novice::DrawLine(int(point1.x + (i / 2)), int(point1.y + a * (i / 2)), int(point2.x + (i / 2)), int(point1.y + a * (i / 2)), color);
		} else {
			int a = int(powf(-1.0f, float(i)));
			Novice::DrawLine(int(point1.x + a * (i / 2)), int(point1.y + (i / 2)), int(point2.x + a * (i / 2)), int(point1.y + (i / 2)), color);
		}
	}

};