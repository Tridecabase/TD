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

///////////////////////////////////////////////////////////////0/1

/// <summary>
/// 数字を描く
/// </summary>
/// <param name="posX">描きたい数字の中心点posX</param>
/// <param name="posY">描きたい数字の中心点posY</param>
/// <param name="width">描きたい数字の横幅</param>
/// <param name="height">描きたい数字の縦幅</param>
/// <param name="color">描きたい色</param>
/// <param name="Num">描きたい数字、今は0が1しができない</param>
void DrawNum(const int posX, const int posY, const int width, const int height, const int color, int Num);

/// <summary>
/// 数字を描く、箱は正方形
/// </summary>
/// <param name="posX">描きたい数字の中心点posX</param>
/// <param name="posY">描きたい数字の中心点posY</param>
/// <param name="width">描きたい数字の横幅</param>
/// <param name="color">描きたい色</param>
/// <param name="Num">描きたい数字、今は0が1しができない</param>
void DrawNum(const int posX, const int posY, const int width, const int color, int Num);