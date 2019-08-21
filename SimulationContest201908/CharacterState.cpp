#include "DXUT.h"
#include "CharacterState.h"

#include "Character.h"


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
			temp.x = character->pos.x + RandomNumber(-50, 50);
			temp.y = character->pos.y + RandomNumber(-50, 50);
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

	GameObject* obj = character->IsCharacterRader(character->attackRader);
	if (obj)
	{
		character->targetObject = obj;
		character->ChangeState(new Character_Attack(character));
		return;
	}
}

void Character_Move::SendStringMessage(string str)
{
}

void Character_Die::Update()
{
	character->destroy = true;
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
}
