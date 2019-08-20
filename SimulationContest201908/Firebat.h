#pragma once
#include "Character.h"


class Firebat :
	public Character
{
public:
	Firebat();
	virtual ~Firebat();

private:
	Gun* gun = nullptr;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();


	// Character��(��) ���� ��ӵ�
	virtual void CharacterAttack() override;

};

