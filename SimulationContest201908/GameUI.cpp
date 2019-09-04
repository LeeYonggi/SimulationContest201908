#include "DXUT.h"
#include "UI.h"
#include "GameUI.h"
#include "GameOperator.h"

GameUI::GameUI()
	: UI(Vector2(SCREEN_X * 0.5f, SCREEN_Y * 0.5f), RESOURCEMANAGER->AddTexture("UI/MainUI.png"))
{
	pos.z = -14;
}

GameUI::~GameUI()
{
}

void GameUI::Init()
{
	switch (GAMEMANAGER->GetStage())
	{
	case STAGE_1:
		miniMapTexture = RESOURCEMANAGER->AddTexture("UI/Minimap1.png");

		break;
	case STAGE_2:
		miniMapTexture = RESOURCEMANAGER->AddTexture("UI/Minimap2.png");

		break;
	case STAGE_3:
		miniMapTexture = RESOURCEMANAGER->AddTexture("UI/Minimap3.png");
		break;
	default:
		break;
	}
	mineralTexture = RESOURCEMANAGER->AddTexture("UI/resources.png");
}

void GameUI::Update()
{

}

void GameUI::Render()
{
	RENDERMANAGER->DrawSprite(miniMapTexture, Vector2(128, 613));
	MiniIconRender();
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, { 1, 1 }, rotate, color);
	RENDERMANAGER->DrawSprite(mineralTexture, Vector2(1125, 50));
	RENDERMANAGER->DrawFont(L"* " + to_wstring(GAMEMANAGER->mineralCount), "fixedsys", Vector2(1150, 40), 40);
	float second = (int)GAMEMANAGER->time % 60;
	float minute = (int)GAMEMANAGER->time / 60;
	WCHAR secondStr[64], minuteStr[64];
	wsprintf(secondStr, L"%02d", (int)second);
	RENDERMANAGER->DrawFont(to_wstring((int)minute) + L" : ", "fixedsys", Vector2(600, 10), 40);
	RENDERMANAGER->DrawFont(secondStr, "fixedsys", Vector2(650, 10), 40);
}

void GameUI::Release()
{
}

void GameUI::MiniIconRender()
{
	auto player1 = OBJECTMANAGER->GetObjectList(PLAYER);
	auto enemy1 = OBJECTMANAGER->GetObjectList(ENEMY);

	for (auto obj : *player1)
	{
		Character* character = static_cast<Character*>(obj);
		if (character->hp > 0)
		{
			RENDERMANAGER->DrawSprite(RESOURCEMANAGER->AddTexture("UI/MiniIcon.png"), 
				Vector2(obj->pos.x * (200.0f / 1200.0f) + 120, 610 - obj->pos.y * (200.0f / 1200.0f)));
		}
	}

	for (auto obj : *enemy1)
	{
		Character* character = static_cast<Character*>(obj);
		if (character->hp > 0 && obj->renderActive)
		{
			RENDERMANAGER->DrawSprite(RESOURCEMANAGER->AddTexture("UI/MiniIcon2.png"),
				Vector2(obj->pos.x * (200.0f / 1200.0f) + 120, 610 - obj->pos.y * (200.0f / 1200.0f)));
		}
	}
}
