#include "DXUT.h"
#include "MouseControll.h"

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
	pos.z = -1;
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


	for (auto obj : *iter)
	{
		if (RectCollision(Vector2(obj->pos), {2, 2}, ))
		{
			selectList.push_back(static_cast<Character*>(obj));
		}
	}
}
