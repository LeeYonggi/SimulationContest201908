#include "DXUT.h"
#include "Firebat.h"

#include "Bullet.h"

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

	vector<Texture*> die;
	die.push_back(RESOURCEMANAGER->AddTexture("Character/dead/firebat_dead.png"));
	animator->AddAnime("Die", new Animation(die, true));

	animator->SetNowAnime("Idle");

	ChangeState(new Character_Idle(this));

	vector<Texture*> anime;
	anime.push_back(RESOURCEMANAGER->AddTexture("Character/firebat/weapon/flamethrower.png"));
	gun = new Gun(anime, this);
	OBJECTMANAGER->AddObject(GUN, gun);
	gun->pivot = { 0, -5 };
	gun->distance = 10.0f;

	moveRadar = 200.0f;
	attackRadar = 100.0f;
	moveSpeed = 140.0f;

	radius = 25.0f;
	shadowPivot = mainTexture->info.Height * 0.5f;

	hp = 30;

	isMoveIdle = true;
}

void Firebat::Update()
{
	Character::Update();
	if (renderActive == false && gun)
		gun->renderActive = false;
	else if(renderActive == true && gun)
		gun->renderActive = true;
	if (gun && hp < 1)
	{
		gun->destroy = true;
		gun = nullptr;
	}
}

void Firebat::Render()
{
	Character::Render();
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Firebat::Release()
{
}

void Firebat::CharacterAttack()
{
	animator->SetNowAnime("Idle");
	if (static_cast<Character*>(targetObject)->hp < 1)
	{
		ChangeState(new Character_Idle(this));
		return;
	}
	if (!CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRadar) && reloadTime > 0.0f)
	{
		ChangeState(new Character_Move(true, this));
		targetPos = Vector2(targetObject->pos);
		reloadTime = 0.0f;
		return;
	}

	Vector2 dir = targetObject->pos - pos;
	D3DXVec2Normalize(&dir, &dir);
	dirVector = dir;

	if (time < 0.0f && reloadTime < 0.0f)
	{
		gun->GunAttack();
		Bullet* bullet = new Bullet(Bullet::FIREBAT, targetObject);
		Vector2 temp = gun->GetShootPos();
		bullet->pos.x = temp.x;
		bullet->pos.y = temp.y;
		
		if (tag == PLAYER)
			OBJECTMANAGER->AddObject(PLAYER_BULLET, bullet);
		else
			OBJECTMANAGER->AddObject(ENEMY_BULLET, bullet);

		time = 0.15f;

		if (reloadTime < -1.0f)
			reloadTime = 1.0f;
	}
	reloadTime -= ELTime;
	time -= ELTime;
}
