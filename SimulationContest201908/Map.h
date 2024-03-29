#pragma once
#include "GameObject.h"

class Map :
	public GameObject
{
public:
	Map();
	virtual ~Map();
private:
	Animator* animator = nullptr;
	
public:
	static Map* nowMap;
public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

