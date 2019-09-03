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
	Vector2 size = Vector2( mainTexture->info.Width, mainTexture->info.Height );
	if (RectCollision(Vector2(pos), size, INPUTMANAGER->GetMouse(), { 2, 2 }))
	{
		if (onPointPress) 
			onPointPress();
		if (isPressOn)
			color.a = 0.5f;

		if (INPUTMANAGER->IsKeyDown(VK_LBUTTON))
			if (onPointEnter) onPointEnter();
	}
	else
		color.a = 1.0f;
}

void UI::Render()
{
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, { 1, 1 }, rotate, color);
}

void UI::Release()
{
}
