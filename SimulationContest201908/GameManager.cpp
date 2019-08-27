#include "DXUT.h"
#include "GameManager.h"

#include "Soldier.h"
#include "MouseControll.h"
#include "Map.h"
#include "Firebat.h"
#include "Tank.h"
#include "GameObject.h"
#include "GameUI.h"

void GameManager::Init()
{
	RESOURCEMANAGER->CreateFontList("fixedsys", 1, 100);

	OBJECTMANAGER->AddObject(GameObject::BACKGROUND1, new Map());
	OBJECTMANAGER->AddObject(GameObject::UI, new GameUI());
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3 + i % 2; j++)
		{
			Vector2 pivot = Vector2(-500 - (i % 2 * 30.0f), -360);
			GameObject* obj = OBJECTMANAGER->AddObject(GameObject::PLAYER, new Soldier());
			obj->pos = { pivot.x + j * 60, pivot.y + i * 60, 0 };
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Vector2 pivot = { -200, 210 };
			GameObject *obj = OBJECTMANAGER->AddObject(GameObject::ENEMY, new Firebat());
			obj->pos = { pivot.x + i * 60, pivot.y + j * 60, 0 };
		}
	}

	OBJECTMANAGER->AddObject(GameObject::MOUSE_CONTROLL, new MouseControll());
	CAMERAMANAGER->pos = {-320, -320, -10};
	CAMERAMANAGER->SetCameraZoomPos({ 0, 0 }, {960, 540});
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
