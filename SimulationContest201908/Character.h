#pragma once
#include "GameObject.h"

#include "CharacterState.h"

class HpUI;
class Effect;
class Character :
	public GameObject
{
public:
	Character();
	virtual ~Character();

protected:
	Character_State *state = nullptr;
	float attackedTime = 0.0f;
	float shadowPivot = 0;

public:
	int hp = 50;
	int maxHp = 50;
	HpUI* hpUI = nullptr;
	float hpPivot = -50.0f;
	GameObject* targetObject = nullptr;
	Animator *animator = nullptr;
	Vector2 dirVector = { 1, 0 };
	Vector2 targetPos = { 0, 0 };
	Effect* shadow = nullptr;
	float moveSpeed = 100.0f;
	float moveRadar = 100.0f;
	float attackRadar = 80.0f;
	float characterTime = 0.0f;
	bool isMoveIdle = false;
	bool isSelect = false;
	bool isFly = false;
	
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
	virtual void CharacterDie();
public:
	string CharacterCollision();
	string FlyCollision();
	GameObject* IsCharacterRader(float radar);
	bool ForgCheck();
	void CharacterAttacked(int damage, Vector2 target);
	bool IsCharacterTargetAttack();
};

