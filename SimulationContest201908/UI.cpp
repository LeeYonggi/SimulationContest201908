#include "DXUT.h"
#include "UI.h"


UI::UI(Vector2 position, Texture* texture)
{
	pos.x = position.x;
	pos.y = position.y;

	mainTexture = texture;
}

UI::~UI()
{
}

void UI::Init()
{

}

void UI::Update()
{

}

void UI::Render()
{
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, rotate, color);
}

void UI::Release()
{
}
