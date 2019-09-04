#pragma once
#include "Character.h"
class Aircraft :
	public Character
{
public:

private:
	float attackDelay = 1.0f;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	// Character��(��) ���� ��ӵ�
	virtual void CharacterAttack() override;

	void PlayerInit();
	void EnemyInit();
};

