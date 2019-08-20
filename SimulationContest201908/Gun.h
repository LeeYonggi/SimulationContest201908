#pragma once
#include "GameObject.h"
class Gun :
	public GameObject
{
public:
	Gun(vector<Texture*> anime, Character *_character);
	virtual ~Gun();

public:
	Animator* animator = nullptr;
	Character* character = nullptr;
	float distance = 8.0f;
	Vector2 pivot = { 0, 0 };

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void GunAttack();
};

