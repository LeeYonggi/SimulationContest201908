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

	Texture* mainTexture = nullptr;
	Texture* attackTexture = nullptr;
	bool isAttack = false;

public:
	void Init();
	void Update();
	void Render();

public:
	bool IsKeyDown(int key) { return (pastKey[key] == false && nowKey[key] == true); }
	bool IsKeyPress(int key) { return (pastKey[key] == true && nowKey[key] == true); }
	bool IsKeyUp(int key) { return (pastKey[key] == true && nowKey[key] == false); }
	void SetAttack(bool value) { isAttack = value; };
	bool GetAttack() { return isAttack; }
	Vector2 GetMouse() { return mouse; }
};

#define INPUTMANAGER InputManager::GetInstance()