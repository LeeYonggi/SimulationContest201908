#pragma once
#include "Character.h"
class Tank :
	public Character
{
public:
	Tank();
	virtual ~Tank();

private:
	float time = 0.0f;
	float reloadTime = 0.0f;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	// Character��(��) ���� ��ӵ�
	virtual void CharacterAttack() override;
};

