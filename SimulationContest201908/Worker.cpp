#include "DXUT.h"
#include "Worker.h"

#include "UI.h"
#include "CreateTower.h"

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

	vector<Texture*> die;
	die.push_back(RESOURCEMANAGER->AddTexture("Character/dead/worker_dead.png"));
	animator->AddAnime("Die", new Animation(die, true));

	animator->SetNowAnime("Idle");

	moveRadar = 150.0f;
	attackRadar = 60.0f;
	radius = 20.0f;
	shadowPivot = mainTexture->info.Height * 0.5f;

	ChangeState(new Character_Idle(this));

	hp = 100;

	buildUI = new UI(Vector2(130, 380), RESOURCEMANAGER->AddTexture("UI/tower_UI.png"));
	OBJECTMANAGER->AddObject(OBJ_UI, buildUI);
	buildUI->pos.z = -14;
	buildUI->SetPressOn(true);
	buildUI->SetPointEnter([=]() 
		{
			CreateTower* towerUI = new CreateTower(this);
			OBJECTMANAGER->AddObject(OBJ_UI, towerUI);
		}
	);

	gun = new Gun(RESOURCEMANAGER->AddAnimeTexture("Character/worker/animation/hammer%d.png", 1, 13),
		this);
	OBJECTMANAGER->AddObject(GUN, gun);
	gun->pivot = { 0, 0 };
	gun->distance = 20.0f;
	gun->animator->GetAnime("Attack")->animeSpeed = 15.0f;

	Character::Init();
}

void Worker::Update()
{
	Character::Update();
	if (renderActive == false && gun)
		gun->renderActive = false;
	else if (renderActive == true && gun)
		gun->renderActive = true;
	if (gun && hp < 1)
	{
		gun->destroy = true;
		gun = nullptr;
	}
	attackDelay -= ELTime;
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
		if(targetObject)
			static_cast<Character*>(targetObject)->hp -= 5;

		gun->animator->SetNowAnime("Attack");
		attackDelay = 1.0f;
	}
}

void Worker::MakeTower(Vector2 targetPos)
{
	this->targetPos = targetPos;
	ChangeState(new Character_CreateTower(this));
	isMakeTower = true;
}

