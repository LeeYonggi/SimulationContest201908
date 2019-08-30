#include "DXUT.h"
#include "Effect.h"

Effect::Effect(Animation* anime, float destroyTime)
{
	animator = new Animator(this);
	animator->AddAnime("Idle", anime);
	animator->SetNowAnime("Idle");
	this->destroyTime = destroyTime;
}

Effect::~Effect()
{
}

void Effect::Init()
{

}

void Effect::Update()
{
	animator->Update();

	if (time > destroyTime)
		destroy = true;
	time += ELTime;
}

void Effect::Render()
{
	if(mainTexture)
		RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color, flip);
}

void Effect::Release()
{
}