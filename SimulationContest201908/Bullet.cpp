#include "DXUT.h"
#include "Bullet.h"


Bullet::Bullet(BULLET_STATE state, GameObject* target)
{
	bulletState = state;
	targetObj = target;
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	switch (bulletState)
	{
	case Bullet::SOLDIER:
		mainTexture = RESOURCEMANAGER->AddTexture("Character/gunner/Gun_Bullet.png");

		moveVector = Vector2(targetObj->pos - pos);

		D3DXVec2Normalize(&moveVector, &moveVector);

		bulletSpeed = 500.0f;

		radius = 5.0f;

		damage = 10;

		break;
	case Bullet::FIREBAT:
		mainTexture = RESOURCEMANAGER->AddTexture("Character/firebat/weapon/fire.png");

		moveVector = Vector2(targetObj->pos - pos);

		D3DXVec2Normalize(&moveVector, &moveVector);
		{
			float temp = RotateToVec2({ 0, 0 }, moveVector);

			moveVector.x = cos(temp + (float)RandomNumber(-3, 3) * 0.1f);
			moveVector.y = sin(temp + (float)RandomNumber(-3, 3) * 0.1f);
		}
		bulletSpeed = RandomNumber(100, 150);

		radius = 5.0f;

		damage = 1;

		growFire = RandomNumber(10, 30) * 0.02f;
		break;
	case Bullet::TANK:
		break;
	default:
		break;
	}
}

void Bullet::Update()
{
	switch (bulletState)
	{
	case Bullet::SOLDIER:
		if (WallCollision(Vector2(pos), { 2, 2 }) || time > 3.0f)
			destroy = true;

		BulletCollision(true);
		break;
	case Bullet::FIREBAT:
		if (time > 1.2f)
			destroy = true;

		if(fireHitTime < 0.0f)
			BulletCollision(false);

		scale.x += growFire * ELTime;
		scale.y += growFire * ELTime;

		fireHitTime -= ELTime;

		break;
	case Bullet::TANK:
		break;
	default:
		break;
	}
	rotate = RotateToVec2(Vector2(pos), Vector2(pos) + moveVector);

	pos.x += moveVector.x * ELTime * bulletSpeed;
	pos.y += moveVector.y * ELTime * bulletSpeed;

	time += ELTime;
}

void Bullet::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color);
}

void Bullet::Release()
{
}

void Bullet::BulletCollision(bool isDestroy)
{
	auto iter = OBJECTMANAGER->GetObjectList(ENEMY);

	if(tag == ENEMY_BULLET)
		iter = OBJECTMANAGER->GetObjectList(PLAYER);

	for (auto obj : *iter)
	{
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius))
		{
			Character* character = static_cast<Character*>(obj);
			character->CharacterAttacked(damage);
			if (isDestroy)
				destroy = true;
			fireHitTime = 0.4f;
		}
	}
}
