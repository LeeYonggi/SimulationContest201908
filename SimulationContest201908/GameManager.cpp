#include "DXUT.h"
#include "GameManager.h"

#include "Soldier.h"
#include "MouseControll.h"
#include "Map.h"
#include "Firebat.h"
#include "Tank.h"
#include "GameObject.h"
#include "GameUI.h"
#include "IngameScene.h"
#include "GameOperator.h"
#include "Aircraft.h"
#include "Worker.h"

void GameManager::Init()
{
	RESOURCEMANAGER->CreateFontList("fixedsys", 1, 100);
	CAMERAMANAGER->screenSize = { 640, 360 };

	switch (stage)
	{
	case STAGE_1:
		Stage1Init();
		break;
	case STAGE_2:
		Stage2Init();
		break;
	case STAGE_3:
		break;
	default:
		break;
	}

	OBJECTMANAGER->AddObject(GameObject::MOUSE_CONTROLL, new MouseControll());
}

void GameManager::Update()
{
	switch (stage)
	{
	case STAGE_1:
		if (LifeCount(GameObject::ENEMY) == 10)
		{
			if (oper)
				oper->SpeechChange(1);
		}
		break;
	case STAGE_2:
		break;
	case STAGE_3:
		break;
	default:
		break;
	}
	if (INPUTMANAGER->IsKeyDown(VK_F1))
	{
		SCENEMANAGER->AddScene(new IngameScene(), true);
		SetStage(STAGE_1);
	}
	if (INPUTMANAGER->IsKeyDown(VK_F2))
	{
		SCENEMANAGER->AddScene(new IngameScene(), true);
		SetStage(STAGE_2);
	}
}

void GameManager::Render()
{
}

void GameManager::Release()
{
}

void GameManager::Stage1Init()
{
	OBJECTMANAGER->AddObject(GameObject::BACKGROUND1, new Map());
	OBJECTMANAGER->AddObject(GameObject::OBJ_UI, new GameUI());
	oper = OBJECTMANAGER->AddObject(GameObject::OBJ_UI, new GameOperator());
	oper->SpeechChange(0);

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
			GameObject* obj = OBJECTMANAGER->AddObject(GameObject::ENEMY, new Firebat());
			obj->pos = { pivot.x + i * 60, pivot.y + j * 60, 0 };
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Vector2 pivot = Vector2(-200, 100);
			GameObject* obj = OBJECTMANAGER->AddObject(GameObject::ENEMY, new Soldier());
			obj->pos = { pivot.x + j * 60, pivot.y + i * 60, 0 };
		}
	}
	GameObject* obj = OBJECTMANAGER->AddObject(GameObject::PLAYER, new Tank());
	obj->pos = { 200, -400, 0 };

	CAMERAMANAGER->pos = { -320, -320, -10 };
	CAMERAMANAGER->SetCameraZoomPos({ 0, 0 }, { 960, 540 });
}

void GameManager::Stage2Init()
{
	OBJECTMANAGER->AddObject(GameObject::BACKGROUND1, new Map());
	OBJECTMANAGER->AddObject(GameObject::OBJ_UI, new GameUI());
	oper = OBJECTMANAGER->AddObject(GameObject::OBJ_UI, new GameOperator());
	oper->SpeechChange(0);

	Vector2 pivot = Vector2(-200, 100);
	GameObject* obj = OBJECTMANAGER->AddObject(GameObject::ENEMY, new Soldier());
	obj->pos = { pivot.x, pivot.y, 0 };


	OBJECTMANAGER->AddObject(GameObject::PLAYER, new Aircraft());
	obj = OBJECTMANAGER->AddObject(GameObject::PLAYER, new Worker());
	obj->pos = {-200, -200, 0};

	CAMERAMANAGER->pos = { -320, -320, -10 };
	CAMERAMANAGER->SetCameraZoomPos({ 0, 0 }, { 960, 540 });
}

void GameManager::Stage3Init()
{
}

int GameManager::LifeCount(GameObject::GAMEOBJECT_TAG tag)
{
	auto iter = OBJECTMANAGER->GetObjectList(tag);
	int life = 0;
	for (auto obj : *iter)
	{
		if(static_cast<Character*>(obj)->hp > 0)
			life += 1;
	}
	return life;
}
