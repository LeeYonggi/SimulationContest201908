#pragma once
#include "Singleton.h"

enum GAME_STAGE
{
	STAGE_1,
	STAGE_2,
	STAGE_3
};
class GameOperator;
class GameManager :
	public Singleton<GameManager>
{
private:
	GAME_STAGE stage = STAGE_1;

public:
	GameOperator* oper = nullptr;

public:
	void Init();
	void Update();
	void Render();
	void Release();

public:
	void Stage1Init();
	void Stage2Init();
	void Stage3Init();

	int LifeCount(GameObject::GAMEOBJECT_TAG tag);

public:
	GAME_STAGE GetStage() { return stage; }
	void SetStage(GAME_STAGE value) { stage = value; }
};

#define GAMEMANAGER GameManager::GetInstance()