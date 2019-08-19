#pragma once
#include "Singleton.h"
class CameraManager :
	public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

public:
	Vector3 pos = {0, 0, -10};
	Vector3 at = { 0, 0, 0 };
	Vector3 up = { 0, 1, 0 };
	Vector2 screenSize = { 640, 360 };

public:
	void Init();
	void ViewSetting();

};

#define CAMERAMANAGER CameraManager::GetInstance()