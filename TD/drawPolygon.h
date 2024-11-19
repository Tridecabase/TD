#pragma once
#include <Novice.h>
#include <Vector2.h>
#include <math.h>

///////////////////////////////////////////////////////////////Polygon

/// <summary>
/// 四角塗りつぶしを描く
/// </summary>
/// <param name="point1">Vector2 point1</param>
/// <param name="point2">Vector2 point2</param>
/// <param name="point4">Vector2 point3</param>
/// <param name="point3">Vector2 point4</param>
/// <param name="color"></param>
void DrawPolygon(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4, const int color);

/// <summary>
/// 五角形塗りつぶしを描く
/// </summary>
/// <param name="point1">Vector2 point1</param>
/// <param name="point2">Vector2 point2</param>
/// <param name="point3">Vector2 point3</param>
/// <param name="point4">Vector2 point4</param>
/// <param name="point5">Vector2 point5</param>
/// <param name="color"></param>
void DrawPolygon(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4
			   , const Vector2 point5, const int color);

/// <summary>
/// 六角形塗りつぶしを描く
/// </summary>
/// <param name="point1">Vector2 point1</param>
/// <param name="point2">Vector2 point2</param>
/// <param name="point3">Vector2 point3</param>
/// <param name="point4">Vector2 point4</param>
/// <param name="point5">Vector2 point5</param>
/// <param name="point6">Vector2 point6</param>
/// <param name="color"></param>
void DrawPolygon(const Vector2 point1, const Vector2 point2, const Vector2 point3, const Vector2 point4
			   , const Vector2 point5, const Vector2 point6, const int color);

///////////////////////////////////////////////////////////////Line


void DrawLineNew(const Vector2 point1, const Vector2 point2, const int px, int color);