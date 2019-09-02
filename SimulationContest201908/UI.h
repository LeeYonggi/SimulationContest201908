#pragma once
#include "GameObject.h"
class UI :
	public GameObject
{
public:
	UI(Vector2 position, Texture *texture);
	virtual ~UI();

protected:
	function<void()> onPointEnter = nullptr;
	function<void()> onPointPress = nullptr;
	bool isPressOn = false;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetPointEnter(function<void()> value) { onPointEnter = value; }
	void SetPointPress(function<void()> value) { onPointPress = value; }
	void SetPressOn(bool value) { isPressOn = value; }
};

