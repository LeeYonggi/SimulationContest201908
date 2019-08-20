#include "DXUT.h"
#include "GameManager.h"

#include "Soldier.h"
#include "MouseControll.h"
#include "Map.h"
#include "Firebat.h"

void GameManager::Init()
{
	OBJECTMANAGER->AddObject(GameObject::BACKGROUND1, new Map());
	
	GameObject * obj = OBJECTMANAGER->AddObject(GameObject::PLAYER, new Soldier());
	obj->pos = {-200, -200, 0};

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
