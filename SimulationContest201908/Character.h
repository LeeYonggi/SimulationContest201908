#pragma once
#include "GameObject.h"

#include "CharacterState.h"

class Character :
	public GameObject
{
public:
	Character();
	virtual ~Character();

protected:
	Character_State *state = nullptr;
	GameObject* targetObject = nullptr;

public:
	Animator *animator = nullptr;
	Vector2 dirVector = { 1, 0 };
	Vector2 targetPos = { 0, 0 };
	float moveSpeed = 100.0f;
	float moveRadar = 100.0f;
	float attackRader = 80.0f;
	bool isDirectAttack = false;
	float characterTime = 0.0f;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	void ChangeState(Character_State *_state)
	{ 
		SAFE_DELETE(state);
		state = _state; 
	}

public:
	virtual void CharacterAttack() = 0;
	void CharacterCollision();
	GameObject* IsCharacterRader(float radar);
};

