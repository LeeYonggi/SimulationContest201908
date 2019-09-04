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
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:

};

