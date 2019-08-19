#include "DXUT.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

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
