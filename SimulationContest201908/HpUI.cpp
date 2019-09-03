#include "DXUT.h"
#include "HpUI.h"

HpUI::HpUI(Character* character)
	: UI(Vector2(character->pos), RESOURCEMANAGER->AddTexture("UI/Hp/Hpside.png"))
{
	pos.z = -11;
	if (character->tag == PLAYER)
		hpTexture = RESOURCEMANAGER->AddTexture("UI/Hp/Hp.png");
	else
		hpTexture = RESOURCEMANAGER->AddTexture("UI/Hp/HpEnemy.png");
	this->character = character;
	scale.y = 0.7f;
	color.a = 0.6f;
}

HpUI::~HpUI()
{
}

void HpUI::Init()
{
}

void HpUI::Update()
{
}

void HpUI::Render()
{
	if (!character->renderActive) return;
	Vector2 length = Vector2(((float)character->hp / (float)character->maxHp), 1);
	Vector2 tempPos = ScreenToWorld(Vector2(character->pos));
	tempPos.y += character->hpPivot;
	RENDERMANAGER->DrawSprite(hpTexture, tempPos, scale, length, rotate, color);
	RENDERMANAGER->DrawSprite(mainTexture, tempPos, scale, {1, 1}, rotate, color);
}

void HpUI::Release()
{
}
