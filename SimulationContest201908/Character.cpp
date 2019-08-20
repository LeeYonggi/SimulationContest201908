#include "DXUT.h"
#include "Character.h"

Character::Character()
{
	animator = new Animator(this);
}

Character::~Character()
{
	SAFE_DELETE(animator);
	SAFE_DELETE(state);
}

void Character::Init()
{
}

void Character::Update()
{
	animator->Update();

	state->Update();

	if (dirVector.x < 0)
		flip.first = true;
	else
		flip.first = false;

	if (attackedTime > 0.0f)
	{
		color = { 1, 0, 0, 1 };
		attackedTime -= ELTime;
	}
	else
		color = { 1, 1, 1, 1 };

	if (hp < 0)
		ChangeState(new Character_Die(this));
}

void Character::Render()
{
}

void Character::Release()
{
}


string Character::CharacterCollision()
{
	auto back = OBJECTMANAGER->GetObjectList(BACKGROUND2);

	for (auto obj : *back)
	{
		Vector2 center, size;
		center.x = obj->pos.x;
		center.y = obj->pos.y - obj->mainTexture->info.Height * 0.25f;
		size.x = obj->mainTexture->info.Width;
		size.y = obj->mainTexture->info.Height * 0.5f;

		if (RectCollision(Vector2(pos), { 10, 10 }, center, size))
		{
			Vector2 dis = obj->pos - pos;

			if (dis.x < 0)
			{
				pos.x += moveSpeed * ELTime;
			}
			else if (dis.x > 0)
			{
				pos.x -= moveSpeed * ELTime;
			}
			if (dis.y < 0)
			{
				pos.y += moveSpeed * ELTime;
			}
			else if (dis.y > 0)
			{
				pos.y -= moveSpeed * ELTime;
			}
		}
	}

	auto character1 = OBJECTMANAGER->GetObjectList(PLAYER);
	if (tag == PLAYER)
		character1 = OBJECTMANAGER->GetObjectList(ENEMY);

	for (auto obj : *character1)
	{
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius))
		{
			Vector2 dis = obj->pos - pos;
			D3DXVec2Normalize(&dis, &dis);

			pos.x -= dis.x * ELTime * moveSpeed;
			pos.y -= dis.y * ELTime * moveSpeed;
		}
	}

	auto character2 = OBJECTMANAGER->GetObjectList(ENEMY);
	if (tag == PLAYER)
		character2 = OBJECTMANAGER->GetObjectList(PLAYER);

	string str = "NONE";
	for (auto obj : *character2)
	{
		if (obj == this) continue;
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius))
		{
			Vector2 dis = obj->pos - pos;
			D3DXVec2Normalize(&dis, &dis);

			pos.x -= dis.x * ELTime * moveSpeed;
			pos.y -= dis.y * ELTime * moveSpeed;
			str = "CollisionStack";
		}
	}
	return str;
}

GameObject* Character::IsCharacterRader(float radar)
{
	auto iter = OBJECTMANAGER->GetObjectList(ENEMY);
	
	if (tag == ENEMY)
		iter = OBJECTMANAGER->GetObjectList(PLAYER);

	for (auto obj : *iter)
	{
		if (CircleCollision(Vector2(obj->pos), 1, Vector2(pos), radar))
		{
			return obj;
		}
	}
	return nullptr;
}

void Character::CharacterAttacked(int damage)
{
	attackedTime = 0.4f;
	hp -= damage;
}
