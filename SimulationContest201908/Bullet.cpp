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

		startVector = Vector2(pos);
		break;
	case Bullet::TANK:
		mainTexture = RESOURCEMANAGER->AddTexture("Character/tank/tank_bullet.png");

		damage = 15;

		radius = 5.0f;

		bulletSpeed = 400;
		startVector = Vector2(pos);

		moveVector = Vector2(targetObj->pos - pos);

		D3DXVec2Normalize(&moveVector, &moveVector);

		{
			float temp = RotateToVec2({ 0, 0 }, moveVector);

			moveVector.x = cos(temp + (float)RandomNumber(-3, 3) * 0.1f);
			moveVector.y = sin(temp + (float)RandomNumber(-3, 3) * 0.1f);
		}

		break;

	case LASER_START:
		mainTexture = RESOURCEMANAGER->AddTexture("Effect/weapon/laser_3.png");

		startVector = Vector2(pos);

		moveVector = Vector2(targetObj->pos - pos);

		D3DXVec2Normalize(&moveVector, &moveVector);

		rotate = RotateToVec2(Vector2(0, 0), moveVector);

		radius = 5.0f;

		scale.y = 0.1f;

		{
			int i = 1;

			while (true)
			{
				Vector2 distance = mainTexture->info.Width * moveVector;

				if (CircleCollision(Vector2(distance * i + Vector2(pos)), radius, Vector2(targetObj->pos), targetObj->radius))
				{
					Bullet* bullet = OBJECTMANAGER->AddObject(tag, new Bullet(LASER_END, targetObj));
					bullet->pos.x = distance.x * i + pos.x;
					bullet->pos.y = distance.y * i + pos.y;
					bullet->rotate = rotate;
					break;
				}
				else
				{
					Bullet* bullet = OBJECTMANAGER->AddObject(tag, new Bullet(LASER_BODY, targetObj));
					bullet->pos.x = distance.x * i + pos.x;
					bullet->pos.y = distance.y * i + pos.y;
					bullet->rotate = rotate;
				}
				i++;
			}
		}
		break;
	case LASER_BODY:
		mainTexture = RESOURCEMANAGER->AddTexture("Effect/weapon/laser_2.png");
		scale.y = 0.1f;
		break;
	case LASER_END:
		mainTexture = RESOURCEMANAGER->AddTexture("Effect/weapon/laser_1.png");
		radius = 5.0f;
		damage = 10.0f;
		scale.y = 0.1f;

		break;
	default:
		break;
	}
	lightTexture = RESOURCEMANAGER->AddTexture("Light/Orange_Light.png");
}

void Bullet::Update()
{
	switch (bulletState)
	{
	case Bullet::SOLDIER:
		if (BulletCollision() || WallCollision(Vector2(pos), { 2, 2 }) || time > 3.0f)
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
		break;
	case Bullet::FIREBAT:
		if(time > 1.2f)
			destroy = true;
		if (fireHitTime < 0.0f)
			BulletCollision();

		scale.x += growFire * ELTime;
		scale.y += growFire * ELTime;

		rotate = RotateToVec2(Vector2(pos), Vector2(pos) + moveVector);

		pos.x += moveVector.x * ELTime * bulletSpeed;
		pos.y += moveVector.y * ELTime * bulletSpeed;
		break;
	case Bullet::TANK:
		if (BulletCollision() || WallCollision(Vector2(pos), { 2, 2 }) || time > 3.0f)
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
		break;
	case LASER_START:
		if (time > 0.5f)
			destroy = true;
		scale.y = Lerp(scale.y, 1.0f, 0.2f);
		break;
	case LASER_BODY:
		if (time > 0.5f)
			destroy = true;
		scale.y = Lerp(scale.y, 1.0f, 0.2f);
		break;
	case LASER_END:
		if (time > 0.5f)
			destroy = true;

		if (fireHitTime < 0.0f && BulletCollision())
		{
			Animation* anime = new Animation(
				RESOURCEMANAGER->AddAnimeTexture("Effect/effect/laser_effect_%d.png", 1, 3),false);
			anime->animeSpeed = 7;
			Effect* effect = new Effect(anime, 0.5f);
			OBJECTMANAGER->AddObject(EFFECT, effect);
			effect->pos = pos;
			effect->scale = {1.5, 1.5};
		}
		scale.y = Lerp(scale.y, 1.0f, 0.2f);
		break;
	default:
		break;
	}

	fireHitTime -= ELTime;
	time += ELTime;
}

void Bullet::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate , color);
}

void Bullet::Release()
{
}

bool Bullet::BulletCollision()
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
			fireHitTime = 0.5f;
			return true;
		}
	}
	return false;
}
