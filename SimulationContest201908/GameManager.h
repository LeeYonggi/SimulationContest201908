#pragma once
#include "Singleton.h"

enum GAME_STAGE
{
	STAGE_1,
	STAGE_2,
	STAGE_3
};
class GameManager :
	public Singleton<GameManager>
{
public:
	GAME_STAGE stage = STAGE_1;

public:
	void Init();
	void Update();
	void Render();
	void Release();
};

#define GAMEMANAGER GameManager::GetInstance()