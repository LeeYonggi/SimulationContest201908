#include "DXUT.h"
#include "Aircraft.h"

void Aircraft::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Character/Aircraft/idle_move/idle1.png");

	Animation* anime = new Animation(
		RESOURCEMANAGER->AddAnimeTexture("Character/Aircraft/idle_move/idle%d.png", 1, 5), true);
	animator->AddAnime("Idle", anime);
	anime = new Animation(
		RESOURCEMANAGER->AddAnimeTexture("Character/Aircraft/idle_move/idle%d.png", 1, 5), true);
	animator->AddAnime("Move", anime);
	anime = new Animation(
		RESOURCEMANAGER->AddAnimeTexture("Character/Aircraft/attack/attack%d.png", 1, 6), false);
	animator->AddAnime("Attack", anime);

	ChangeState(new Character_Idle(this));

	radius = 20.0f;
	moveSpeed = 120.0f;
	moveRadar = 200.0f;
	attackRadar = 150.0f;
}

void Aircraft::Update()
{
	Character::Update();
}

void Aircraft::Render()
{
	Character::Render();
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Aircraft::Release()
{
}

void Aircraft::CharacterAttack()
{
}
