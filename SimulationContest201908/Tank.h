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
	// Character을(를) 통해 상속됨
	virtual void CharacterAttack() override;
};

