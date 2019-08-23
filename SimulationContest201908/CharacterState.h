#pragma once

class Character;
class Character_State
{
public:
	Character_State(Character* _character)
		: character(_character) { }
	virtual ~Character_State() { }
public:
	string stateName;

protected:
	Character* character = nullptr;

public:
	virtual void Update() = 0;
	virtual void SendStringMessage(string str) = 0;
};

class Character_Idle
	: public Character_State
{
private:
	float time = 0.0f;
	int moveCount = 0.0f;
public:
	Character_Idle(Character* _character);
	virtual ~Character_Idle()
	{

	}
public:
	// Character_State을(를) 통해 상속됨
	virtual void Update() override;

	// Character_State을(를) 통해 상속됨
	virtual void SendStringMessage(string str) override;
};

class Character_Move
	: public Character_State
{
private:
	bool isDirectAttack = false;
	float targetCircle = 10.0f;

public:
	Character_Move(bool _isDirectAttack, Character* _character);
	virtual ~Character_Move()
	{

	}
public:
	// Character_State을(를) 통해 상속됨
	virtual void Update() override;

	// Character_State을(를) 통해 상속됨
	virtual void SendStringMessage(string str) override;
};

class Character_Die
	: public Character_State
{
public:
	Character_Die(Character* _character)
		: Character_State(_character)
	{
		stateName = "Die";
	}
	virtual ~Character_Die()
	{

	}
public:
	// Character_State을(를) 통해 상속됨
	virtual void Update() override;

	// Character_State을(를) 통해 상속됨
	virtual void SendStringMessage(string str) override;
};

class Character_Attack
	: public Character_State
{
public:
	Character_Attack(Character* _character)
		: Character_State(_character)
	{
		stateName = "Attack";
	}
	virtual ~Character_Attack()
	{

	}
public:
	// Character_State을(를) 통해 상속됨
	virtual void Update() override;

	// Character_State을(를) 통해 상속됨
	virtual void SendStringMessage(string str) override;
};