#include "DXUT.h"
#include "SBubble.h"

#include <algorithm>

SBubble::SBubble()
	: UI(Vector2(640, 550), RESOURCEMANAGER->AddTexture("UI/talk/talk1.png"))
{
	pos.z = -12;
}

SBubble::~SBubble()
{
	SAFE_DELETE(animator);
}

void SBubble::Init()
{
	vector<Texture*> texture = RESOURCEMANAGER->AddAnimeTexture("UI/talk/talk%d.png", 1, 8);
	animator = new Animator(this);
	animator->AddAnime("Open", new Animation(texture, false));
	animator->GetAnime("Open")->animeSpeed = 13;
	std::reverse(texture.begin(), texture.end());
	animator->AddAnime("Close", new Animation(texture, false));
	animator->SetNowAnime("Open");
	animator->GetAnime("Close")->animeSpeed = 13;
}

void SBubble::Update()
{
	animator->Update();
	if (animator->GetFrameEnd() && animator->GetNowAnimeName() == "Close")
		active = false;
}

void SBubble::Render()
{
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, rotate, color);
}

void SBubble::Release()
{
}
