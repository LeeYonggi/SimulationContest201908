#pragma once
#include "GameObject.h"
class Bullet :
	public GameObject
{
public:
	enum BULLET_STATE
	{
		SOLDIER,
		FIREBAT,
		TANK,
		LASER_START,
		LASER_BODY,
		LASER_END
	};

public:
	Bullet(BULLET_STATE state, GameObject *target);
	virtual ~Bullet();

private:
	BULLET_STATE bulletState;
	GameObject* targetObj;
	Vector2 moveVector = { 0, 0 };
	float time = 0.0f;
	float bulletSpeed = 500.0f;
	int damage = 1.0f;
	float growFire = 0.0f;
	float fireHitTime = 0.0f;

	Vector2 targetVector = { 0, 0 };
	Vector2 startVector = { 0, 0 };
	Vector2 speed = { 0, 0 };
	float velocity = 0.0f;
	float endTime = 0;
	float height = 0;
	float endheight = 0;
	float maxTime = 1.0f;


public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	bool BulletCollision();

};

