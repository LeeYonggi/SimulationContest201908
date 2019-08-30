#include "DXUT.h"
#include "InputManager.h"

InputManager::InputManager()
{
	Init();
}

InputManager::~InputManager()
{
}

void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

	ShowCursor(false); 

	mainTexture = RESOURCEMANAGER->AddTexture("UI/Cursor/Cursor.png");
	attackTexture = RESOURCEMANAGER->AddTexture("UI/Cursor/Attack_Cursor.png");
}

void InputManager::Update()
{
	memcpy(pastKey, nowKey, sizeof(nowKey));
	
	for (int i = 0; i < MAX_KEY; i++)
		nowKey[i] = GetAsyncKeyState(i) & 0x8000;

	POINT temp;
	GetCursorPos(&temp);
	ScreenToClient(DXUTGetHWND(), &temp);
	mouse.x = temp.x;
	mouse.y = temp.y;
}

void InputManager::Render()
{
	if(isAttack)
		RENDERMANAGER->DrawSprite(attackTexture, mouse);
	else
		RENDERMANAGER->DrawSprite(mainTexture, mouse);
}
