#include "DXUT.h"
#include "Worker.h"

Worker::Worker()
{
}

Worker::~Worker()
{
}

void Worker::Init()
{
	mainTexture = RESOURCEMANAGER->AddTexture("Character/worker/idle/idle1.png");

	animator->AddAnime("Idle",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/worker/idle/idle%d.png", 1, 4), true));

	animator->AddAnime("Move",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/worker/run/run%d.png", 1, 6), true));

	animator->AddAnime("Attack",
		new Animation(RESOURCEMANAGER->AddAnimeTexture("Character/worker/idle/idle%d.png", 1, 4), false));

	vector<Texture*> die;
	die.push_back(RESOURCEMANAGER->AddTexture("Character/dead/worker_dead.png"));
	animator->AddAnime("Die", new Animation(die, true));

	animator->SetNowAnime("Idle");

	moveRadar = 100.0f;
	attackRadar = 50.0f;
	radius = 20.0f;
	shadowPivot = mainTexture->info.Height * 0.5f;

	ChangeState(new Character_Idle(this));

	hp = 100;
}

void Worker::Update()
{
	Character::Update();
}

void Worker::Render()
{
	Character::Render();
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Worker::Release()
{
}

void Worker::CharacterAttack()
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
		static_cast<Character*>(targetObject)->hp -= 5;

		animator->SetNowAnime("Attack");
		attackDelay = 1.0f;
	}
}
