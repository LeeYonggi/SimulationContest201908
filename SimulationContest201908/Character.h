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
	float moveSpeed = 100.0f;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	void ChangeState(CHARACTER_STATE _state) { state = _state; }

public:
	void CharacterStayIdle();
	void CharacterMove();
	void CharacterDie();
};
