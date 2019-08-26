#include "DXUT.h"
#include "Tank.h"

#include "Bullet.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

void Tank::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Character/tank/idle/tank1.png");

	animator->AddAnime("Idle",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/tank/idle/tank%d.png", 1, 4), true));

	animator->AddAnime("Move",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/tank/run/run%d.png", 1, 2), true));

	animator->AddAnime("Attack",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/tank/attack/attack%d.png", 1, 6), false));

	animator->SetNowAnime("Idle");

	moveRadar = 300.0f;
	attackRader = 300.0f;

	ChangeState(new Character_Idle(this));
	hp = 100;
}

void Tank::Update()
{
	Character::Update();
	
}

void Tank::Render()
{
	Character::Render();
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Tank::Release()
{
}

void Tank::CharacterAttack()
{
	if(animator->GetNowAnimeName() != "Attack" || animator->GetFrameEnd() == true)
		animator->SetNowAnime("Attack");
	if (static_cast<Character*>(targetObject)->hp < 0)
	{
		ChangeState(new Character_Idle(this));
		return;
	}
	if (!CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRader))
	{
		ChangeState(new Character_Move(true, this));
		targetPos = Vector2(targetObject->pos);
		return;
	}

	Vector2 dir = targetObject->pos - pos;
	D3DXVec2Normalize(&dir, &dir);
	dirVector = dir;

	if (animator->GetNowFrame() == 0)
	{
		Bullet* bullet = new Bullet(Bullet::TANK, targetObject);
		bullet->pos.x = pos.x + dirVector.x * 30;
		bullet->pos.y = pos.y;

		if (tag == PLAYER)
			OBJECTMANAGER->AddObject(PLAYER_BULLET, bullet);
		else
			OBJECTMANAGER->AddObject(ENEMY_BULLET, bullet);

		//animator->SetNowAnime("Attack");
	}
}
