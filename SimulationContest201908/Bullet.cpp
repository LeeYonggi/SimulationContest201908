#include "DXUT.h"
#include "Bullet.h"

#include "DamageFont.h"
#include "Effect.h"

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

		if (tag == ENEMY_BULLET)	
			damage = 5;
		else
			damage = 10;

		lightTexture = RESOURCEMANAGER->AddTexture("Light/Orange_Light.png");

		startVector = Vector2(pos);
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

		damage = 5;

		growFire = RandomNumber(10, 30) * 0.02f;

		lightTexture = RESOURCEMANAGER->AddTexture("Light/Orange_Light.png");

		startVector = Vector2(pos);
		break;
	case Bullet::TANK:
		mainTexture = RESOURCEMANAGER->AddTexture("Character/tank/tank_bullet.png");

		damage = 15;

		radius = 5.0f;

		lightTexture = RESOURCEMANAGER->AddTexture("Light/Orange_Light.png");
		bulletSpeed = 400;
		startVector = Vector2(pos);

		/*
		targetVector = Vector2(targetObj->pos);

		endheight = targetVector.y - startVector.y;
		if(targetVector.y > startVector.y)
			height = (targetVector.y + 100) - targetVector.y;
		else
			height = (startVector.y + 100) - targetVector.y;

		velocity = 2 * height / (maxTime * maxTime);
		speed.y = sqrt(2 * velocity * height);

		{
			float a = velocity;
			float b = -2 * speed.y;
			float c = 2 * endheight;

			endTime = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

			speed.x = -(startVector.x - targetVector.x) / endTime;
		}*/

		moveVector = Vector2(targetObj->pos - pos);

		D3DXVec2Normalize(&moveVector, &moveVector);

		{
			float temp = RotateToVec2({ 0, 0 }, moveVector);

			moveVector.x = cos(temp + (float)RandomNumber(-3, 3) * 0.1f);
			moveVector.y = sin(temp + (float)RandomNumber(-3, 3) * 0.1f);
		}

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
		if (BulletCollision(true) || WallCollision(Vector2(pos), { 2, 2 }) || time > 3.0f)
		{
			destroy = true;

			Animation* anime = new Animation(RESOURCEMANAGER->AddAnimeTexture("Effect/bullet_effect/effect%d.png", 1, 6),
				false);
			anime->animeSpeed = 10;
			Effect* effect = new Effect(anime, 0.5f);
			OBJECTMANAGER->AddObject(EFFECT, effect);
			effect->pos = pos;
		}
		rotate = RotateToVec2(Vector2(pos), Vector2(pos) + moveVector);

		pos.x += moveVector.x * ELTime * bulletSpeed;
		pos.y += moveVector.y * ELTime * bulletSpeed;
		time += ELTime;
		break;
	case Bullet::FIREBAT:
		if(time > 1.2f)
			destroy = true;
		if (fireHitTime < 0.0f || time > 1.2f)
			BulletCollision(false);

		scale.x += growFire * ELTime;
		scale.y += growFire * ELTime;

		fireHitTime -= ELTime;
		rotate = RotateToVec2(Vector2(pos), Vector2(pos) + moveVector);

		pos.x += moveVector.x * ELTime * bulletSpeed;
		pos.y += moveVector.y * ELTime * bulletSpeed;
		time += ELTime;

		break;
	case Bullet::TANK:
		if (BulletCollision(true) || WallCollision(Vector2(pos), { 2, 2 }) || time > 3.0f)
		{
			destroy = true;

			Animation* anime = new Animation(RESOURCEMANAGER->AddAnimeTexture("Effect/explosion/effect%d.png", 1, 8),
				false);
			anime->animeSpeed = 10;
			Effect* effect = new Effect(anime, 0.7f);
			OBJECTMANAGER->AddObject(EFFECT, effect);
			effect->pos = pos;
		}

		pos.x += moveVector.x * ELTime * bulletSpeed;
		pos.y += moveVector.y * ELTime * bulletSpeed;

		{
			float temp = RotateToVec2({ 0, 0 }, moveVector);

			moveVector.x = cos(temp + (float)RandomNumber(-3, 3) * 0.03f);
			moveVector.y = sin(temp + (float)RandomNumber(-3, 3) * 0.03f);
		}
		
		rotate = RotateToVec2(Vector2(pos), Vector2(pos) + moveVector);

		time += ELTime;
		break;
	default:
		break;
	}

}

void Bullet::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate , color);
}

void Bullet::Release()
{
}

bool Bullet::BulletCollision(bool isDestroy)
{
	auto iter = OBJECTMANAGER->GetObjectList(ENEMY);

	if(tag == ENEMY_BULLET)
		iter = OBJECTMANAGER->GetObjectList(PLAYER);

	for (auto obj : *iter)
	{
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius) && 
			static_cast<Character*>(obj)->hp > 0)
		{
			Character* character = static_cast<Character*>(obj);
			character->CharacterAttacked(damage, startVector);
			DamageFont* damageFont = new DamageFont(Vector2(pos), damage);
			OBJECTMANAGER->AddObject(UI, damageFont);
			if (isDestroy)
				return true;
			fireHitTime = 0.5f;
		}
	}
	return false;
}
