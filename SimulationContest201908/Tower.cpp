#include "DXUT.h"
#include "Tower.h"

#include "Bullet.h"
#include "Effect.h"

void Tower::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Tower/tower/maked_tower/maked_tower1.png");

	animator->AddAnime("Idle",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Tower/tower/maked_tower/maked_tower%d.png", 1, 8), true));

	animator->AddAnime("Move",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Tower/tower/maked_tower/maked_tower%d.png", 1, 8), true));

	Animation* buildAnime = new Animation(RESOURCEMANAGER->AddAnimeTexture("Tower/making_tower/making%d.png", 1, 7), true);
	animator->AddAnime("Build", buildAnime);

	vector<Texture*> die;
	die.push_back(RESOURCEMANAGER->AddTexture("Character/dead/Tower_Die.png"));
	animator->AddAnime("Die", new Animation(die, true));

	animator->SetNowAnime("Build");

	moveSpeed = 0.0f;

	radius = 30;
	moveRadar = 200.0f;
	attackRadar = 200;
	shadowPivot = mainTexture->info.Height * 0.3f;
	pos.z = 0.0f;

	shadow->scale = {3, 3};
}

void Tower::Update()
{
	Character::Update();
	if(gun)
		gun->pos.z = pos.z - 1;
	if (renderActive == false && gun)
		gun->renderActive = false;
	else if (renderActive == true && gun)
		gun->renderActive = true;
	if (gun && hp < 1)
	{
		gun->destroy = true;
		gun = nullptr;
	}

	if (buildDelay > 4.0f && animator->GetNowAnimeName() == "Build")
	{
		animator->SetNowAnime("Idle");
		gun = new Gun(RESOURCEMANAGER->AddAnimeTexture("Tower/tower/gun/gun.png", 1, 1),
			this);
		OBJECTMANAGER->AddObject(GUN, gun);
		gun->pivot = { 0, 50 };
		gun->distance = 23.0f;
		gun->animator->GetAnime("Attack")->animeSpeed = 15.0f;
		ChangeState(new Character_Idle(this));
	}
	buildDelay += ELTime;
	attackDelay -= ELTime;
}

void Tower::Render()
{
	Character::Render();
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Tower::Release()
{
}

void Tower::CharacterAttack()
{
	if (!gun) return;
	animator->SetNowAnime("Idle");

	if (static_cast<Character*>(targetObject)->hp < 1)
	{
		ChangeState(new Character_Idle(this));
		return;
	}
	if (!CircleCollision(Vector2(targetObject->pos), 1, Vector2(pos), attackRadar) && attackDelay < 0.0f)
	{
		ChangeState(new Character_Move(true, this));
		targetPos = Vector2(targetObject->pos);
		return;
	}

	Vector2 dir = targetObject->pos - pos;
	D3DXVec2Normalize(&dir, &dir);
	dirVector = dir;

	if (attackDelay < 0.0f)
	{
		gun->GunAttack();

		Bullet* bullet = new Bullet(Bullet::SOLDIER, targetObject);
		Vector2 temp = gun->GetShootPos();
		bullet->pos.x = temp.x;
		bullet->pos.y = temp.y;
		if (tag == PLAYER)
			OBJECTMANAGER->AddObject(PLAYER_BULLET, bullet);
		else
			OBJECTMANAGER->AddObject(ENEMY_BULLET, bullet);
		attackDelay = 0.5f;
	}
}

void Tower::CharacterDie()
{

}
