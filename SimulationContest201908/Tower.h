#pragma once
#include "Character.h"
class Tower :
	public Character
{
private:
	Gun* gun = nullptr;
	float attackDelay = 0.5f;
	float buildDelay = 0.0f;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	// Character��(��) ���� ��ӵ�
	virtual void CharacterAttack() override;
	virtual void CharacterDie();

};

