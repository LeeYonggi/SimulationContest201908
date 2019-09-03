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
	pos.z = -11;
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
	AttackObject();
	if (INPUTMANAGER->IsKeyDown(VK_RBUTTON))
	{
		MoveObject();
	}

	if (isControll)
		CameraControll();
	if (INPUTMANAGER->IsKeyDown('1'))
		isControll = !isControll;

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
		Character* character = static_cast<Character*>(obj);
		if (RectCollision(Vector2(obj->pos), {2, 2}, center, size) &&
			character->hp > 0)
		{
			selectList.push_back(character);
			character->isSelect = true;
		}
		else
		{
			character->isSelect = false;
		}
	}
}

void MouseControll::MoveObject()
{
	Vector2 mouse = WorldToScreen(INPUTMANAGER->GetMouse());

	for (auto iter : selectList)
	{
		if (INPUTMANAGER->GetAttack())
		{
			iter->targetObject = targetCharacter;
			iter->SendMessageState("ChangeMoveDirect");
		}
		else
		{
			iter->SendMessageState("ChangeMove");
			iter->targetPos = mouse;
			iter->targetObject = nullptr;
		}
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

void MouseControll::AttackObject()
{
	auto iter = OBJECTMANAGER->GetObjectList(ENEMY);
	Vector2 mouse = WorldToScreen(INPUTMANAGER->GetMouse());

	for (auto obj : *iter)
	{
		if (obj->mainTexture == nullptr || static_cast<Character*>(obj)->hp < 1 || !obj->renderActive)
			continue;
		Vector2 size = Vector2( obj->mainTexture->info.Width, obj->mainTexture->info.Height );

		if (RectCollision(mouse, {2, 2}, Vector2(obj->pos), size))
		{
			INPUTMANAGER->SetAttack(true);
			targetCharacter = static_cast<Character*>(obj);
			return;
		}
	}
	targetCharacter = nullptr;
	INPUTMANAGER->SetAttack(false);
}

void MouseControll::SelectAll()
{
	selectList.clear();
	auto iter = OBJECTMANAGER->GetObjectList(PLAYER);

	for (auto obj : *iter)
	{
		Character* character = static_cast<Character*>(obj);

		selectList.push_back(character);
		character->isSelect = true;
	}
}

void MouseControll::RemoveSelectObject(Character* character)
{
	selectList.remove(character);
}
