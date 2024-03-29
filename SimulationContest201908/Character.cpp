#include "DXUT.h"
#include "Character.h"

#include "MouseControll.h"
#include "Effect.h"
#include "HpUI.h"

Character::Character()
{
	animator = new Animator(this);
	lightTexture = RESOURCEMANAGER->AddTexture("Light/light.png");

	vector<Texture*> vTexture;
	vTexture.push_back(RESOURCEMANAGER->AddTexture("Character/Shadow.png"));
	shadow = new Effect(new Animation(vTexture, true));
	OBJECTMANAGER->AddObject(EFFECT, shadow);
	shadow->pos.x = pos.x;
	shadow->pos.y = pos.y + shadowPivot;
	shadow->pos.z = 1;

}

Character::~Character()
{
	SAFE_DELETE(animator);
	SAFE_DELETE(state);
	shadow->destroy = true;
}

void Character::Init()
{
	hpUI = new HpUI(this);
	OBJECTMANAGER->AddObject(OBJ_UI, hpUI);
	maxHp = hp;
}

void Character::Update()
{
	animator->Update();

	if(state)
		state->Update();

	if (dirVector.x < 0)
		flip.first = true;
	else
		flip.first = false;

	if (tag == ENEMY)
		renderActive = ForgCheck();

	if (state && hp < 1 && state->stateName != "Die")
	{
		ChangeState(new Character_Die(this));
		if (isSelect)
		{
			auto iter = *OBJECTMANAGER->GetObjectList(GAMEOBJECT_TAG::MOUSE_CONTROLL);
			static_cast<MouseControll*>((*iter.begin()))->RemoveSelectObject(this);
			isSelect = false;
		}
	}
	else if (hp < 1)
		return;

	if (attackedTime > 0.0f)
	{
		color = { 1, 0, 0, 1 };
		attackedTime -= ELTime;
	}
	else
		color = { 1, 1, 1, 1 };

	shadow->pos.x = pos.x;
	shadow->pos.y = pos.y - shadowPivot;
	shadow->renderActive = renderActive;
}

void Character::Render()
{
	if (isSelect)
		RENDERMANAGER->DrawImage(RESOURCEMANAGER->AddTexture("Character/CharacterTarget.png"), 
			Vector3(pos.x, pos.y - shadowPivot, pos.z), scale);
}

void Character::Release()
{
}


void Character::CharacterDie()
{
}

string Character::CharacterCollision()
{
	auto back = OBJECTMANAGER->GetObjectList(BACKGROUND2);
	string str = "NONE";
	if (isFly)
		return FlyCollision();

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
			str = "CollisionStack";
		}
	}

	auto character1 = OBJECTMANAGER->GetObjectList(PLAYER);

	if (tag == PLAYER)
		character1 = OBJECTMANAGER->GetObjectList(ENEMY);

	for (auto obj : *character1)
	{
		if (static_cast<Character*>(obj)->isFly == true) continue;
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius) &&
			static_cast<Character*>(obj)->hp > 0)
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

	for (auto obj : *character2)
	{
		if (obj == this) continue;
		if (static_cast<Character*>(obj)->isFly == true) continue;
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius) &&
			static_cast<Character*>(obj)->hp > 0)
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

string Character::FlyCollision()
{
	string str = "NONE";
	auto character1 = OBJECTMANAGER->GetObjectList(PLAYER);

	if (tag == PLAYER)
		character1 = OBJECTMANAGER->GetObjectList(ENEMY);

	for (auto obj : *character1)
	{
		if (static_cast<Character*>(obj)->isFly == false) continue;
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius) &&
			static_cast<Character*>(obj)->hp > 0)
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

	for (auto obj : *character2)
	{
		if (obj == this) continue;
		if (static_cast<Character*>(obj)->isFly == false) continue;
		if (CircleCollision(Vector2(obj->pos), obj->radius, Vector2(pos), radius) &&
			static_cast<Character*>(obj)->hp > 0)
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
		if (CircleCollision(Vector2(obj->pos), 1, Vector2(pos), radar) && static_cast<Character*>(obj)->hp > 0)
		{
			return obj;
		}
	}
	return nullptr;
}

bool Character::ForgCheck()
{
	auto iter = OBJECTMANAGER->GetObjectList(PLAYER);

	for (auto obj : *iter)
	{
		Character* character = static_cast<Character*>(obj);

		if (CircleCollision(Vector2(character->pos), character->moveRadar, Vector2(pos), radius)
			&& character->hp > 0)
		{
			return true;
		}
	}
	return false;
}

void Character::CharacterAttacked(int damage, Vector2 target)
{
	attackedTime = 0.4f;
	hp -= damage;
	if (state->stateName == "Idle")
	{
		ChangeState(new Character_Move(true, this));
		targetPos = target;
	}
}

bool Character::IsCharacterTargetAttack()
{
	if (!targetObject) return false;

	Character* target = static_cast<Character*>(targetObject);
	
	return (CircleCollision(Vector2(target->pos), 1, Vector2(pos), attackRadar) && static_cast<Character*>(target)->hp > 0);
}
