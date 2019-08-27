#include "DXUT.h"
#include "UI.h"
#include "GameUI.h"

GameUI::GameUI()
	: UI(Vector2(SCREEN_X * 0.5f, SCREEN_Y * 0.5f), RESOURCEMANAGER->AddTexture("UI/minimap.png"))
{
	pos.z = -11;
}

GameUI::~GameUI()
{
}

void GameUI::Init()
{

}

void GameUI::Update()
{
}

void GameUI::Render()
{
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, rotate, color);
}

void GameUI::Release()
{
}
