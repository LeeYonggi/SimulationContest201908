#pragma once
#include "Character.h"

class Gun;
class Soldier :
	public Character
{
public:
	Gun* gun = nullptr;
	float attackDelay = 0.5f;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	// Character을(를) 통해 상속됨
	virtual void CharacterAttack() override;
};

