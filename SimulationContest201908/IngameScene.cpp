#include "DXUT.h"
#include "IngameScene.h"


void IngameScene::Init()
{
	GAMEMANAGER->Init();
}

void IngameScene::Update()
{
	GAMEMANAGER->Update();
}

void IngameScene::Render()
{
	GAMEMANAGER->Render();
}

void IngameScene::Release()
{
}
