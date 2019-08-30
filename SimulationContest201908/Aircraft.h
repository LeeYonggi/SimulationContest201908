#pragma once
#include "Character.h"
class Aircraft :
	public Character
{
public:


public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	// Character을(를) 통해 상속됨
	virtual void CharacterAttack() override;
};

