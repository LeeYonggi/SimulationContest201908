#pragma once
#include "Singleton.h"

#define MAX_KEY 256

class InputManager :
	public Singleton<InputManager>
{
public:
	InputManager();
	virtual ~InputManager();

private:
	bool nowKey[MAX_KEY];
	bool pastKey[MAX_KEY];
	Vector2 mouse = { 0, 0 };

public:
	void Init();
	void Update();

public:
	bool IsKeyDown(int key) { return (pastKey[key] == false && nowKey[key] == true); }
	bool IsKeyPress(int key) { return (pastKey[key] == true && nowKey[key] == true); }
	bool IsKeyUp(int key) { return (pastKey[key] == true && nowKey[key] == false); }
	Vector2 GetMouse() { return mouse; }
};

#define INPUTMANAGER InputManager::GetInstance()