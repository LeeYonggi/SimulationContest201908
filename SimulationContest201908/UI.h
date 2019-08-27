#pragma once
#include "GameObject.h"
class UI :
	public GameObject
{
public:
	UI(Vector2 position, Texture *texture);
	virtual ~UI();

private:


public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

