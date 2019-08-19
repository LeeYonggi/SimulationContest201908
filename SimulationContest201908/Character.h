#pragma once
#include "GameObject.h"


class Character :
	public GameObject
{
	using CharacterState = void(Character::*)(void);
public:
	Character();
	virtual ~Character();

public:
	enum CHARACTER_STATE
	{
		IDLE,
		MOVE,
		DIE,
		END
	};

protected:
	Animator *animator = nullptr;
	CHARACTER_STATE state = IDLE;
	CharacterState stateFunc[CHARACTER_STATE::END];

public:
	Vector2 dirVector = { 1, 0 };
	Vector2 targetPos = { 0, 0 };

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	void CharacterStayIdle();
	void CharacterMove();
	void CharacterDie();
};
