#include "DXUT.h"
#include "Utility.h"

float RotateToVec2(Vector2 p1, Vector2 p2)
{
	return atan2f(p2.y - p1.y, p2.x - p1.x);
}

bool RectCollision(Vector2 p1, Vector2 size1, Vector2 p2, Vector2 size2)
{
	RECT re = { 0 };
	RECT re1 = {
		int(p1.x - size1.x * 0.5f),
		int(p1.y - size1.y * 0.5f),
		int(p1.x + size1.x * 0.5f),
		int(p1.y + size1.y * 0.5f)
	};
	RECT re2 = {
		int(p2.x - size2.x * 0.5f),
		int(p2.y - size2.y * 0.5f),
		int(p2.x + size2.x * 0.5f),
		int(p2.y + size2.y * 0.5f)
	};

	return IntersectRect(&re, &re1, &re2);
}

Vector2 WorldToScreen(Vector2 p1)
{
	Vector2 temp = { CAMERAMANAGER->pos.x, CAMERAMANAGER->pos.y };
	Vector2 screenSize = CAMERAMANAGER->screenSize;
	
	screenSize.x = screenSize.x / (float)SCREEN_X;
	screenSize.y = screenSize.y / (float)SCREEN_X;

	temp.x += p1.x - screenSize.x * SCREEN_X;
	temp.y += p1.y - screenSize.y * SCREEN_Y;
	return temp;
}
