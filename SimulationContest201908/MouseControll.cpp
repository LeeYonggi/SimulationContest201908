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
	if (INPUTMANAGER->IsKeyDown(VK_RBUTTON))
	{
		MoveObject();
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
		}
	}
}

void MouseControll::MoveObject()
{
	Vector2 mouse = WorldToScreen(INPUTMANAGER->GetMouse());

	for (auto iter : selectList)
	{
		iter->ChangeState(Character::MOVE);
		iter->targetPos = mouse;
	}
}
