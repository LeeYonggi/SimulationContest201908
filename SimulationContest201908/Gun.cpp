#include "DXUT.h"
#include "Gun.h"

Gun::Gun(vector<Texture*> anime, Character* _character)
{
	animator = new Animator(this);
	
	Animation* animation = new Animation(anime, false);

	animator->AddAnime("Attack", animation);
	
	vector<Texture*> idle;

	idle.push_back(anime[anime.size() - 1]);
	animation = new Animation(idle, false);
	animator->AddAnime("Idle", animation);
	animator->SetNowAnime("Idle");
	mainTexture = anime[anime.size() - 1];

	character = _character;
}

Gun::~Gun()
{
	SAFE_DELETE(animator);
}

void Gun::Init()
{
}

void Gun::Update()
{
	rotate = atan2f(character->dirVector.y, character->dirVector.x);

	pos.x = pivot.x + character->pos.x + character->dirVector.x * distance;
	pos.y = pivot.y + character->pos.y + character->dirVector.y * distance;
	pos.z = 0;
	if (character->dirVector.x < 0)
		flip.second = true;
	else
		flip.second = false;

	animator->Update();
}

void Gun::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Gun::Release()
{
}

void Gun::GunAttack()
{
	animator->SetNowAnime("Attack");
}
