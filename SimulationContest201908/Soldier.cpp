#include "DXUT.h"
#include "Soldier.h"

#include "Gun.h"

void Soldier::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Character/gunner/idle/idle1.png");

	animator->AddAnime("Idle",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/idle/idle%d.png", 1, 4), true));

	animator->AddAnime("Move",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/run/gunner_run%d.png", 1, 6), true));

	animator->SetNowAnime("Idle");

	stateFunc[IDLE] = &Character::CharacterStayIdle;
	stateFunc[MOVE] = &Character::CharacterMove;
	stateFunc[ATTACK] = &Character::CharacterAttack;
	stateFunc[DIE] = &Character::CharacterDie;

	gun = new Gun(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/effect/effect%d.png", 1, 7),
		this);
	OBJECTMANAGER->AddObject(GUN, gun);
	gun->pivot = {0, -5};
	gun->distance = 10.0f;
	gun->animator->GetAnime("Attack")->animeSpeed = 50.0f;
	radius = 25.0f;
	moveSpeed = 120.0f;
}

void Soldier::Update()
{
	Character::Update();
	(this->*stateFunc[state])();
}

void Soldier::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Soldier::Release()
{
}

void Soldier::CharacterAttack()
{
	animator->SetNowAnime("Idle");
	
	if (!targetObject || !CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRader))
	{
		ChangeState(MOVE);
		isDirectAttack = true;
		return;
	}

	Vector2 dir = targetObject->pos - pos;
	D3DXVec2Normalize(&dir, &dir);
	dirVector = dir;

	gun->GunAttack();
}
