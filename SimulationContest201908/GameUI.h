#pragma once
#include "UI.h"

class GameUI
	: public UI
{
public:
	GameUI();
	virtual ~GameUI();

private:

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

