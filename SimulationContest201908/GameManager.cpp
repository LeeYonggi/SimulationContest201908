#include "DXUT.h"
#include "GameManager.h"

#include "Soldier.h"
#include "MouseControll.h"
#include "Map.h"
#include "Firebat.h"

void GameManager::Init()
{
	OBJECTMANAGER->AddObject(GameObject::BACKGROUND1, new Map());
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Vector2 pivot = { -500, -360 };
			GameObject* obj = OBJECTMANAGER->AddObject(GameObject::PLAYER, new Soldier());
			obj->pos = { pivot.x + i * 60, pivot.y + j * 60, 0 };
		}
	}

	OBJECTMANAGER->AddObject(GameObject::ENEMY, new Firebat());
	OBJECTMANAGER->AddObject(GameObject::UI, new MouseControll());
	CAMERAMANAGER->pos = {-320, -320, -10};
	//CAMERAMANAGER->SetCameraZoomPos({ 0, 0 }, {960, 540});
}

void GameManager::Update()
{
}

void GameManager::Render()
{
}

void GameManager::Release()
{
}
