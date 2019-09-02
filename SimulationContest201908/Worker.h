#pragma once
#include "Character.h"

class UI;
class Worker :
	public Character
{
public:
	Worker();
	virtual ~Worker();

private:
	float attackDelay = 1.0f;
	UI* buildUI = nullptr;
	bool isMakeTower = false;

public:
	Gun* gun = nullptr;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	// Character��(��) ���� ��ӵ�
	virtual void CharacterAttack() override;
	void MakeTower(Vector2 targetPos);

};
