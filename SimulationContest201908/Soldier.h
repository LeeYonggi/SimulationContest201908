#pragma once
#include "Character.h"

class Gun;
class Soldier :
	public Character
{
public:
	Gun* gun = nullptr;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

