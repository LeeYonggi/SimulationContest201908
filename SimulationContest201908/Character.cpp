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
	animator->SetNowAnime("Idle");

}

void Character::CharacterMove()
{
	animator->SetNowAnime("Move");

	Vector2 moveVector = { 0, 0 };
	moveVector = targetPos - Vector2(pos);
	D3DXVec2Normalize(&moveVector, &moveVector);

	pos.x += moveVector.x * ELTime * moveSpeed;
	pos.y += moveVector.y * ELTime * moveSpeed;

	if (Vec2Distance(Vector2(pos), targetPos) < 10.0f)
		state = IDLE;
}

void Character::CharacterDie()
{

}
