#pragma once
#include "GameObject.h"
class DamageFont :
	public GameObject
{
public:
	DamageFont(Vector2 targetPos, int damage);
	virtual ~DamageFont();

private:
	int damage = 0;
	float time = 0.0f;
	Vector2 startPos = { 0, 0 };
	Vector2 startCameraPos = { 0, 0 };
	Vector2 movePos = { 0, 0 };

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

