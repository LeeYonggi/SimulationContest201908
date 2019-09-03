#pragma once
#include "UI.h"


class HpUI :
	public UI
{
public:
	HpUI(Character* character);
	virtual ~HpUI();

private:
	Character* character = nullptr;
	Texture* hpTexture = nullptr;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

