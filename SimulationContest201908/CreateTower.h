#pragma once
#include "UI.h"

class Worker;
class CreateTower :
	public UI
{
public:
	CreateTower(Worker *worker);
	virtual ~CreateTower();

private:
	Worker* worker = nullptr;

public:
	float time = 0.0f;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

