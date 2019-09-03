#include "DXUT.h"
#include "CreateTower.h"

#include "Tower.h"
#include "Worker.h"

CreateTower::CreateTower(Worker* worker)
	: UI(INPUTMANAGER->GetMouse(), RESOURCEMANAGER->AddTexture("Tower/tower/maked_tower/maked_tower1.png"))
{
	pos.z = -11;
	this->worker = worker;
}

CreateTower::~CreateTower()
{
}

void CreateTower::Init()
{
	color = Color(0, 1, 0, 0.5f);
}

void CreateTower::Update()
{
	pos.x = INPUTMANAGER->GetMouse().x;
	pos.y = INPUTMANAGER->GetMouse().y;

	if (INPUTMANAGER->IsKeyDown(VK_LBUTTON) && time > 0.5f)
	{
		destroy = true;
		worker->MakeTower(WorldToScreen(Vector2(pos)));
	}
	time += ELTime;
}

void CreateTower::Render()
{
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, {1, 1}, rotate, color);
}

void CreateTower::Release()
{
}
