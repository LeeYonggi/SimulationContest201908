#pragma once
#include "Character.h"
class Worker :
	public Character
{
public:
	Worker();
	virtual ~Worker();

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

};

