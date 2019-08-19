#include "DXUT.h"
#include "Soldier.h"

#include "Gun.h"

void Soldier::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Character/gunner/idle/idle1.png");

	animator->AddAnime("Idle",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/idle/idle%d.png", 1, 4), true));
	animator->SetNowAnime("Idle");

	stateFunc[state] = &Character::CharacterStayIdle;
	stateFunc[state] = &Character::CharacterMove;
	stateFunc[state] = &Character::CharacterDie;

	gun = new Gun(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/effect/effect%d.png", 1, 7),
		this);
	OBJECTMANAGER->AddObject(GUN, gun);
	gun->pivot = {0, -5};
}

void Soldier::Update()
{
	Character::Update();
	(this->*stateFunc[state])();
}

void Soldier::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, { 0, 0, 0 });
}

void Soldier::Release()
{
}
