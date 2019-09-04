#pragma once
#include "Scene.h"

class UI;
class MainScene :
	public Scene
{
private:
	UI* startUi = nullptr;
	UI* mainUi = nullptr;
	UI* title = nullptr;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:

};

