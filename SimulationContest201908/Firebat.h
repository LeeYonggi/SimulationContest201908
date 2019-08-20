#pragma once
#include "Character.h"


class Firebat :
	public Character
{
public:
	Firebat();
	virtual ~Firebat();

private:
	Gun* gun = nullptr;
	float time = 0.0f;
	float reloadTime = 0.0f;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();


	// Character을(를) 통해 상속됨
	virtual void CharacterAttack() override;

};

