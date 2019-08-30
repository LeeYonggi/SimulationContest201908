#pragma once
#include "UI.h"

class GameOperator;
class GameUI
	: public UI
{
public:
	GameUI();
	virtual ~GameUI();

private:
	Texture* miniMapTexture = nullptr;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void MiniIconRender();
};

