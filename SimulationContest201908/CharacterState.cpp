#include "DXUT.h"
#include "CharacterState.h"

#include "Character.h"


void Character_Idle::Update()
{
	if (isMoving)
	{
		time -= ELTime;

		if (time < 0.0f)
		{
			Vector2 temp;
			temp.x = RandomNumber(-50, 50);
			temp.y = RandomNumber(-50, 50);
			character->targetPos = temp;
			character->ChangeState(new Character_Move(true, character));
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
}

void Character_Move::Update()
{
}

void Character_Move::SendStringMessage(string str)
{
}

void Character_Die::Update()
{
}

void Character_Die::SendStringMessage(string str)
{
}

void Character_Attack::Update()
{
}

void Character_Attack::SendStringMessage(string str)
{
}
