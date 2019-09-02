#include "DXUT.h"
#include "Tank.h"

#include "Bullet.h"
#include "Effect.h"

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

	vector<Texture*> die;
	die.push_back(RESOURCEMANAGER->AddTexture("Character/dead/dead.png"));
	animator->AddAnime("Die", new Animation(die, true));

	animator->SetNowAnime("Idle");

	moveRadar = 250.0f;
	attackRadar = 250.0f;
	shadowPivot = mainTexture->info.Height * 0.5f;
	shadow->scale = {3, 3};

	radius = 30.0f;

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
	if (static_cast<Character*>(targetObject)->hp < 1)
	{
		ChangeState(new Character_Idle(this));
		return;
	}
	if (!CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRadar))
	{
		ChangeState(new Character_Move(true, this));
		targetPos = Vector2(targetObject->pos);
		return;
	}

	Vector2 dir = targetObject->pos - pos;
	D3DXVec2Normalize(&dir, &dir);
	dirVector = dir;

	if (attackDelay < 0)
	{
		for (float i = 0; i < 3; i += 1)
		{
			Bullet* bullet = new Bullet(Bullet::TANK, targetObject);

			float temp = RotateToVec2({ 0, 0 }, dirVector);

			Vector2 tempVector;
			tempVector.x = cos(temp + -0.5 + i * 0.5f);
			tempVector.y = sin(temp + -0.5 + i * 0.5f);

			bullet->pos.x = pos.x + dirVector.x * 30 + tempVector.x;
			bullet->pos.y = pos.y + tempVector.y;

			if (tag == PLAYER)
				OBJECTMANAGER->AddObject(PLAYER_BULLET, bullet);
			else
				OBJECTMANAGER->AddObject(ENEMY_BULLET, bullet);
		}


		//animator->SetNowAnime("Attack");
		attackDelay = 2.0f;
		animator->SetNowFrame(0);
		animator->SetNowAnime("Attack");
	}
	attackDelay -= ELTime;
}

void Tank::CharacterDie()
{
	if (isDieBomb) return;

	Animation* anime = new Animation(RESOURCEMANAGER->AddAnimeTexture("Effect/explosion/effect%d.png", 1, 8),
		false);
	anime->animeSpeed = 10;
	Effect* effect = new Effect(anime, 0.7f);
	OBJECTMANAGER->AddObject(EFFECT, effect);
	effect->pos = pos;
	effect->scale = { 2, 2 };

	isDieBomb = true;
}
