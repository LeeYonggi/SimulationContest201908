#include "DXUT.h"
#include "Soldier.h"

#include "Gun.h"
#include "Bullet.h"

void Soldier::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Character/gunner/idle/idle1.png");

	animator->AddAnime("Idle",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/idle/idle%d.png", 1, 4), true));

	animator->AddAnime("Move",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/run/gunner_run%d.png", 1, 6), true));

	animator->SetNowAnime("Idle");

	ChangeState(new Character_Idle(this));

	gun = new Gun(RESOURCEMANAGER->AddAnimeTexture("Character/gunner/effect/effect%d.png", 1, 7),
		this);
	OBJECTMANAGER->AddObject(GUN, gun);
	gun->pivot = {0, -5};
	gun->distance = 10.0f;
	gun->animator->GetAnime("Attack")->animeSpeed = 15.0f;
	radius = 20.0f;
	moveSpeed = 120.0f;

	moveRadar = 200.0f;
	attackRader = 150.0f;
}

void Soldier::Update()
{
	Character::Update();
	if (gun && hp < 0)
	{
		gun->destroy = true;
		gun = nullptr;
	}
}

void Soldier::Render()
{
	Character::Render();
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Soldier::Release()
{
}

void Soldier::CharacterAttack()
{
	animator->SetNowAnime("Idle");
	
	if (static_cast<Character*>(targetObject)->hp < 0)
	{
		ChangeState(new Character_Idle(this));
		return;
	}
	if (!CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRader) && gun->animator->GetFrameEnd())
	{
		ChangeState(new Character_Move(true, this));
		targetPos = Vector2(targetObject->pos);
		return;
	}

	Vector2 dir = targetObject->pos - pos;
	D3DXVec2Normalize(&dir, &dir);
	dirVector = dir;

	if (gun->animator->GetFrameEnd())
	{
		gun->GunAttack();
		Bullet* bullet = new Bullet(Bullet::SOLDIER, targetObject);
		Vector2 temp = gun->GetShootPos();
		bullet->pos.x = temp.x;
		bullet->pos.y = temp.y;
		if(tag == PLAYER)
			OBJECTMANAGER->AddObject(PLAYER_BULLET, bullet);
		else
			OBJECTMANAGER->AddObject(ENEMY_BULLET, bullet);
	}
}
