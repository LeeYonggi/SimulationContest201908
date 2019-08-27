#include "DXUT.h"
#include "Utility.h"

float RotateToVec2(Vector2 p1, Vector2 p2)
{
	return atan2f(p2.y - p1.y, p2.x - p1.x);
}

float AbsRotate(float rot)
{
	if (rot < 0)
		rot = -rot;
	else
		rot = D3DX_PI * 2 - rot;

	return rot;
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
	screenSize.y = screenSize.y / (float)SCREEN_Y;

	temp.x += screenSize.x * (p1.x - SCREEN_X * 0.5f);
	temp.y += screenSize.y * (SCREEN_Y * 0.5f -  p1.y);
	return temp;
}

Vector2 ScreenToWorld(Vector2 p1)
{
	Vector2 temp = { CAMERAMANAGER->pos.x, CAMERAMANAGER->pos.y };
	Vector2 screenSize = CAMERAMANAGER->screenSize;

	screenSize.x = (float)SCREEN_X / screenSize.x;
	screenSize.y = (float)SCREEN_Y / screenSize.y;

	temp.x = (p1.x - temp.x) * screenSize.x + SCREEN_X * 0.5f;
	temp.y = SCREEN_Y * 0.5f - (p1.y - temp.y) * screenSize.y;
	return temp;
}

float Vec2Distance(Vector2 p1, Vector2 p2)
{
	Vector2 temp = p2 - p1;
	float d = temp.x * temp.x + temp.y * temp.y;

	return sqrt(d);
}

int RandomNumber(int low, int high)
{
	std::random_device rd; 
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> die(low, high);

	return die(mersenne);
}

bool CircleCollision(Vector2 p1, float r1, Vector2 p2, float r2)
{
	return (Vec2Distance(p1, p2) < r1 + r2);
}

bool WallCollision(Vector2 p1, Vector2 _size)
{
	auto back = OBJECTMANAGER->GetObjectList(GameObject::BACKGROUND2);

	for (auto obj : *back)
	{
		Vector2 center, size;
		center.x = obj->pos.x;
		center.y = obj->pos.y - obj->mainTexture->info.Height * 0.25f;
		size.x = obj->mainTexture->info.Width;
		size.y = obj->mainTexture->info.Height * 0.5f;

		if (RectCollision(Vector2(p1), _size, center, size))
		{
			return true;
		}
	}
	return false;
}
