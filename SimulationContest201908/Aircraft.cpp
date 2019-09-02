#include "DXUT.h"
#include "Aircraft.h"

#include "Bullet.h"
#include "Effect.h"

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
	hp = 100;
	shadow->scale = { 4, 4 };
	isFly = true;

	shadowPivot = mainTexture->info.Height;
	pos.z = -1;
}

void Aircraft::Update()
{
	Character::Update();
	attackDelay -= ELTime;
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
	if (static_cast<Character*>(targetObject)->hp < 1)
	{
		ChangeState(new Character_Idle(this));
		return;
	}
	if (!CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRadar) && animator->GetFrameEnd())
	{
		ChangeState(new Character_Move(true, this));
		targetPos = Vector2(targetObject->pos);
		return;
	}

	if (attackDelay < 0.0f)
	{
		Bullet* bullet = new Bullet(Bullet::LASER_START, targetObject);

		Vector2 temp = Vector2(targetObject->pos - pos);
		bullet->pos.x = pos.x + (temp.x / abs(temp.x)) * mainTexture->info.Width * 0.5f;
		bullet->pos.y = pos.y;
		bullet->pos.z = 0;

		if (tag == PLAYER)
			OBJECTMANAGER->AddObject(PLAYER_BULLET, bullet);
		else
			OBJECTMANAGER->AddObject(ENEMY_BULLET, bullet);

		animator->SetNowAnime("Attack");
		attackDelay = 1.0f;
	}
}
