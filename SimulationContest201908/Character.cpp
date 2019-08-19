#include "DXUT.h"
#include "Character.h"

Character::Character()
{
	animator = new Animator(this);

}

Character::~Character()
{
	SAFE_DELETE(animator);
}

void Character::Init()
{
}

void Character::Update()
{
	animator->Update();
}

void Character::Render()
{
}

void Character::Release()
{
}

void Character::CharacterStayIdle()
{

}

void Character::CharacterMove()
{

}

void Character::CharacterDie()
{

}
