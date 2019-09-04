#pragma once
#include "GameObject.h"
class Mineral :
	public GameObject
{
public:
	Mineral(Vector2 nowPos);
	virtual ~Mineral();

private:
	float firstY = 0;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

