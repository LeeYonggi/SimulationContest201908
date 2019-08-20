#include "DXUT.h"
#include "Firebat.h"

Firebat::Firebat()
{
}

Firebat::~Firebat()
{
}

void Firebat::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Character/firebat/idle/idle1.png");

	animator->AddAnime("Idle",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/firebat/idle/idle%d.png", 1, 4), true));

	animator->AddAnime("Move",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/firebat/run/run%d.png", 1, 6), true));

	animator->SetNowAnime("Idle");

	stateFunc[IDLE] = &Character::CharacterMoveIdle;
	stateFunc[MOVE] = &Character::CharacterMove;
	stateFunc[ATTACK] = &Character::CharacterAttack;
	stateFunc[DIE] = &Character::CharacterDie;

	vector<Texture*> anime;
	anime.push_back(RESOURCEMANAGER->AddTexture("Character/firebat/weapon/flamethrower.png"));
	gun = new Gun(anime, this);
	OBJECTMANAGER->AddObject(GUN, gun);
	gun->pivot = { 0, -5 };
	gun->distance = 10.0f;
}

void Firebat::Update()
{
	Character::Update();
	(this->*stateFunc[state])();
}

void Firebat::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Firebat::Release()
{
}

void Firebat::CharacterAttack()
{
	animator->SetNowAnime("Idle");
	if (!targetObject || !CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRader))
	{
		ChangeState(MOVE);
		isDirectAttack = true;
	}

	Vector2 dir = targetObject->pos - pos;
	D3DXVec2Normalize(&dir, &dir);
	dirVector = dir;
}
