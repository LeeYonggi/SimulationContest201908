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
	// GameObject을(를) 통해 상속됨
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	// Character을(를) 통해 상속됨
	virtual void CharacterAttack() override;
	virtual void CharacterDie();

};

