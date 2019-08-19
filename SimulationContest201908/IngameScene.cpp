#include "DXUT.h"
#include "IngameScene.h"

#include "Soldier.h"
#include "MouseControll.h"

void IngameScene::Init()
{
	OBJECTMANAGER->AddObject(GameObject::PLAYER, new Soldier());
	OBJECTMANAGER->AddObject(GameObject::UI, new MouseControll());
}

void IngameScene::Update()
{
}

void IngameScene::Render()
{
}

void IngameScene::Release()
{
}
