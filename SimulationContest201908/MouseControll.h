#pragma once
#include "GameObject.h"
class MouseControll :
	public GameObject
{
public:
	MouseControll();
	virtual ~MouseControll();
public:

private:
	Vector2 firstPos = { 0, 0 };
	Vector2 endPos = { 0, 0 };
	bool isPress = false;
	list<Character*> selectList;
	

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SelectObject();
	void MoveObject();
	void CameraControll();
public:
	void RemoveSelectObject(Character* character);
};

