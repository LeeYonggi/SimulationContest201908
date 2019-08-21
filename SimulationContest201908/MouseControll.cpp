#include "DXUT.h"
#include "MouseControll.h"

#include "Map.h"
#include "Character.h"


MouseControll::MouseControll()
{
}

MouseControll::~MouseControll()
{
}

void MouseControll::Init()
{
}

void MouseControll::Update()
{
	if (INPUTMANAGER->IsKeyDown(VK_LBUTTON))
	{
		firstPos = INPUTMANAGER->GetMouse();
		endPos = INPUTMANAGER->GetMouse();
		isPress = true;
	}
	if (INPUTMANAGER->IsKeyUp(VK_LBUTTON))
	{
		endPos = INPUTMANAGER->GetMouse();
		isPress = false;
		SelectObject();
	}
	if (INPUTMANAGER->IsKeyPress(VK_LBUTTON))
	{
		endPos = INPUTMANAGER->GetMouse();
	}
	if (INPUTMANAGER->IsKeyDown(VK_RBUTTON))
	{
		MoveObject();
	}
	CameraControll();
	pos.z = -10;
}

void MouseControll::Render()
{
	if (isPress)
		RENDERMANAGER->DrawLine(firstPos, endPos, 4, {0, 1, 0, 1});
}

void MouseControll::Release()
{
}

void MouseControll::SelectObject()
{
	selectList.clear();
	auto iter = OBJECTMANAGER->GetObjectList(PLAYER);

	Vector2 first = WorldToScreen(firstPos);
	Vector2 end = WorldToScreen(endPos);
	Vector2 size = end - first;
	Vector2 center = first + size * 0.5f;

	size.x = abs(size.x);
	size.y = abs(size.y);

	for (auto obj : *iter)
	{
		if (RectCollision(Vector2(obj->pos), {2, 2}, center, size))
		{
			selectList.push_back(static_cast<Character*>(obj));
			static_cast<Character*>(obj)->isSelect = true;
		}
	}
}

void MouseControll::MoveObject()
{
	Vector2 mouse = WorldToScreen(INPUTMANAGER->GetMouse());

	for (auto iter : selectList)
	{
		iter->SendMessageState("ChangeMove");
		iter->targetPos = mouse;
	}
}

void MouseControll::CameraControll()
{
	Vector2 mouse = INPUTMANAGER->GetMouse();
	Texture* background = Map::nowMap->mainTexture;
	constexpr float speed = 4.0f;

	if (mouse.x < 10.0f && CAMERAMANAGER->pos.x > (CAMERAMANAGER->screenSize.x - background->info.Width) * 0.5f)
	{
		CAMERAMANAGER->pos.x -= speed;
	}
	if (mouse.x > SCREEN_X - 10 && CAMERAMANAGER->pos.x < (background->info.Width - CAMERAMANAGER->screenSize.x) * 0.5f)
	{
		CAMERAMANAGER->pos.x += speed;
	}
	if (mouse.y < 10.0f && CAMERAMANAGER->pos.y < (background->info.Height - CAMERAMANAGER->screenSize.y) * 0.5f)
	{
		CAMERAMANAGER->pos.y += speed;
	}
	if (mouse.y > SCREEN_Y - 10 && CAMERAMANAGER->pos.y > (CAMERAMANAGER->screenSize.y - background->info.Height) * 0.5f)
	{
		CAMERAMANAGER->pos.y -= speed;
	}

	if (mouse.x < 0 || mouse.x > SCREEN_X ||
		mouse.y < 0 || mouse.y > SCREEN_Y)
	{
		POINT temp = { max(0, min(mouse.x, SCREEN_X)), max(0, min(mouse.y, SCREEN_Y)) };
		
		ClientToScreen(DXUTGetHWND(), &temp);
		SetCursorPos(temp.x, temp.y);
	}
}

void MouseControll::RemoveSelectObject(Character* character)
{
	selectList.remove(character);
}
