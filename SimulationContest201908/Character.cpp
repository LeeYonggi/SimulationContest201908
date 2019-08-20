#include "DXUT.h"
#include "Character.h"

Character::Character()
{
	animator = new Animator(this);
	state = new Character_Idle(false);
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
	if (dirVector.x < 0)
		flip.first = true;
	else
		flip.first = false;

}

void Character::Render()
{
}

void Character::Release()
{
}


void Character::CharacterMove()
{
	animator->SetNowAnime("Move");

	Vector2 moveVector = { 0, 0 };
	moveVector = targetPos - Vector2(pos);
	D3DXVec2Normalize(&moveVector, &moveVector);
	if (moveVector.x < 0)
		dirVector.x = -1;
	else
		dirVector.x = 1;

	pos.x += moveVector.x * ELTime * moveSpeed;
	pos.y += moveVector.y * ELTime * moveSpeed;

	if (Vec2Distance(Vector2(pos), targetPos) < 10.0f)
		ChangeState(IDLE);

	CharacterCollision();
	
	if (isDirectAttack == false) return;

	GameObject* obj = IsCharacterRader(attackRader);
	if (obj)
	{
		targetObject = obj;
		ChangeState(ATTACK);
	}
}


void Character::CharacterDie()
{

}

void Character::CharacterCollision()
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
