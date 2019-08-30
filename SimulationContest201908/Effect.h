#pragma once
#include "GameObject.h"
class Effect :
	public GameObject
{
public:
	Effect(Animation *anime, float destroyTime);
	virtual ~Effect();

private:
	Animator* animator = nullptr;
	float time = 0.0f;
	float destroyTime = 0.0f;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

