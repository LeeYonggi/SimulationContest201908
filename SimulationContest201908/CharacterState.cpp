#include "DXUT.h"
#include "CharacterState.h"

#include "Character.h"
#include "Tower.h"
#include "Worker.h"
#include "HpUI.h"
#include "Map.h"

Character_Idle::Character_Idle(Character* _character) 
	: Character_State(_character)
{
	character->animator->SetNowAnime("Idle");
	stateName = "Idle";
	if (character->isMoveIdle)
		time = RandomNumber(5, 10) * 0.1f;
}

void Character_Idle::Update()
{
	if (character->isMoveIdle)
	{
		time -= ELTime;

		if (time < 0.0f)
		{
			Vector2 temp;
			Vector2 limit;
			limit.x = (Map::nowMap->mainTexture->info.Width * 0.5f);
			limit.y = (Map::nowMap->mainTexture->info.Height * 0.5f);
			temp.x = character->pos.x + RandomNumber(-50, 50);
			temp.y = character->pos.y + RandomNumber(-50, 50);
			if (temp.x > limit.x)
				int a = 10;
			if (temp.y > limit.y)
				int a = 10;
			temp.x = min(max(temp.x, -limit.x), limit.x);
			temp.y = min(max(temp.y, -limit.y), limit.y);
			if (WallCollision(Vector2(temp), Vector2(20, 20)))
			{
				moveCount += 1;
				if (moveCount > 50)
				{
					character->isMoveIdle = false;
					character->ChangeState(new Character_Idle(character));
					return;
				}
				Update();
				return;
			}
			character->targetPos = temp;
			character->ChangeState(new Character_Move(true, character));
			return;
		}
	}
	GameObject* obj = character->IsCharacterRader(character->moveRadar);
	if (obj)
	{
		character->targetPos = Vector2(obj->pos);
		character->ChangeState(new Character_Move(true, character));
	}
}

void Character_Idle::SendStringMessage(string str)
{
	if (str == "ChangeMoveDirect")
	{
		character->targetPos = Vector2(character->targetObject->pos);
		character->ChangeState(new Character_Move(true, character));
		return;
	}
	if (str == "ChangeMove")
	{
		character->ChangeState(new Character_Move(false, character));
		return;
	}
}

Character_Move::Character_Move(bool _isDirectAttack, Character* _character) 
	: Character_State(_character)
{
	isDirectAttack = _isDirectAttack;
	character->animator->SetNowAnime("Move");
	stateName = "Move";
}

void Character_Move::Update()
{
	Vector2 moveVector = { 0, 0 };
	
	moveVector = character->targetPos - Vector2(character->pos);
	D3DXVec2Normalize(&moveVector, &moveVector);

	if (moveVector.x < 0)
		character->dirVector.x = -1;
	else
		character->dirVector.x = 1;

	character->pos.x += moveVector.x * ELTime * character->moveSpeed;
	character->pos.y += moveVector.y * ELTime * character->moveSpeed;

	if (character->CharacterCollision() == "CollisionStack")
	{
		targetCircle += 1;
	}

	if (Vec2Distance(Vector2(character->pos), character->targetPos) < targetCircle)
	{
		character->ChangeState(new Character_Idle(character));
		return;
	}

	if (isDirectAttack == false) return;

	GameObject* obj = character->IsCharacterRader(character->attackRadar);
	if (obj)
	{
		character->targetObject = obj;
		character->ChangeState(new Character_Attack(character));
		return;
	}
}

void Character_Move::SendStringMessage(string str)
{
	if (str == "ChangeMoveDirect" && character->targetObject)
	{
		if (character->IsCharacterTargetAttack())
			character->ChangeState(new Character_Attack(character));
		else
		{
			character->targetPos = Vector2(character->targetObject->pos);
			isDirectAttack = true;
		}
		return;
	}
}

Character_Die::Character_Die(Character* _character)
	: Character_State(_character)
{
	character->lightTexture = nullptr;
	stateName = "Die";
	if (character->hpUI)
		character->hpUI->destroy = true;
}

void Character_Die::Update()
{
	character->animator->SetNowAnime("Die");
	character->color = Color(color, color, color, color * 1.5f);
	if (color > 0.4f)
		color -= ELTime;
	if (time < 0)
		character->destroy = true;
	character->CharacterDie();
	time -= ELTime;
}

void Character_Die::SendStringMessage(string str)
{

}

void Character_Attack::Update()
{
	character->CharacterAttack();
}

void Character_Attack::SendStringMessage(string str)
{
	if (str == "ChangeMove")
	{
		character->ChangeState(new Character_Move(false, character));
		return;
	}
	if (str == "ChangeMoveDirect")
	{
		if(character->IsCharacterTargetAttack())
		{
			character->ChangeState(new Character_Attack(character));
		}
		else
			character->ChangeState(new Character_Move(true, character));
		return;
	}
}

Character_CreateTower::Character_CreateTower(Character* _character)
	: Character_State(_character)
{
	stateName = "CreateTower";
	character->animator->SetNowAnime("Move");
}

void Character_CreateTower::Update()
{
	Vector2 moveVector = { 0, 0 };

	if (Vec2Distance(Vector2(character->pos), character->targetPos) < targetCircle)
	{
		Worker* worker = static_cast<Worker*>(character);
		
		if(worker->gun->animator->GetNowAnimeName() != "Attack")
			worker->gun->animator->SetNowAnime("Attack");
		else if (worker->gun->animator->GetFrameEnd())
		{
			Tower* tower = new Tower();
			OBJECTMANAGER->AddObject(GameObject::PLAYER, tower);
			tower->pos.x = character->pos.x;
			tower->pos.y = character->pos.y;
			character->pos.y -= 40;
			worker->gun->animator->SetNowAnime("Idle");
			character->ChangeState(new Character_Idle(character));
		}
		return;
	}

	moveVector = character->targetPos - Vector2(character->pos);
	D3DXVec2Normalize(&moveVector, &moveVector);

	if (moveVector.x < 0)
		character->dirVector.x = -1;
	else
		character->dirVector.x = 1;

	character->pos.x += moveVector.x * ELTime * character->moveSpeed;
	character->pos.y += moveVector.y * ELTime * character->moveSpeed;

	if (character->CharacterCollision() == "CollisionStack")
	{
		targetCircle += 1;
	}
}

void Character_CreateTower::SendStringMessage(string str)
{
}
