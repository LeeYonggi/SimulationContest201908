#include "DXUT.h"
#include "Mineral.h"

Mineral::Mineral(Vector2 nowPos)
{
	mainTexture = RESOURCEMANAGER->AddTexture("UI/resources.png");
	pos.x = nowPos.x;
	pos.y = nowPos.y;
	firstY = nowPos.y;
	pos.z = -2;
	scale = { 0.7f, 0.7f };
}

Mineral::~Mineral()
{
}

void Mineral::Init()
{
}

void Mineral::Update()
{
	pos.y = Lerp(pos.y, firstY + 30, 0.1f);
	color.a = Lerp(color.a, 0.0f, 0.03f);

	if (color.a < 0.25f)
	{
		destroy = true;
		GAMEMANAGER->mineralCount += 1;
	}
}

void Mineral::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color);
}

void Mineral::Release()
{
}
