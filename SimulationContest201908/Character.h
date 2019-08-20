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
	float attackedTime = 0.0f;

public:
	int hp = 50;
	GameObject* targetObject = nullptr;
	Animator *animator = nullptr;
	Vector2 dirVector = { 1, 0 };
	Vector2 targetPos = { 0, 0 };
	float moveSpeed = 100.0f;
	float moveRadar = 100.0f;
	float attackRader = 80.0f;
	float characterTime = 0.0f;
	bool isMoveIdle = false;

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
	void SendMessageState(string str)
	{
		if (state)
			state->SendStringMessage(str);
	}

public:
	virtual void CharacterAttack() = 0;
	string CharacterCollision();
	GameObject* IsCharacterRader(float radar);
	void CharacterAttacked(int damage);
};

