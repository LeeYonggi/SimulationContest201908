#include "DXUT.h"
#include "DamageFont.h"


DamageFont::DamageFont(Vector2 targetPos, int damage)
{
	Vector2 nowPos = ScreenToWorld(targetPos);
	pos.x = nowPos.x;
	pos.y = nowPos.y;
	pos.z = -11;

	startPos = nowPos;
	startCameraPos = Vector2(CAMERAMANAGER->pos);

	this->damage = damage;
}

DamageFont::~DamageFont()
{
}

void DamageFont::Init()
{
}

void DamageFont::Update()
{
	if (time > 1.0f)
		destroy = true;
	
	pos.x = startPos.x - (CAMERAMANAGER->pos.x - startCameraPos.x) * 2 + movePos.x;
	pos.y = startPos.y + (CAMERAMANAGER->pos.y - startCameraPos.y) * 2 + movePos.y;

	movePos.y -= ELTime * 30;
	color.a -= ELTime * 3;

	time += ELTime;
}

void DamageFont::Render()
{
	RENDERMANAGER->DrawFont(to_wstring(damage), "fixedsys", Vector2(pos), max(min(damage * 4, 50), 20), color);
}

void DamageFont::Release()
{
}
