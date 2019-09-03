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
	Vector2 cameraZoomPos = { 0, 0 };
	Vector2 pastZoomPos = { 0, 0 };
	Vector2 zoomSize = { 0, 0 };
	pair<bool, bool> isCameraZoom = make_pair(false, false);
	float cameMoveSpeed = 0.05f;
	float time = 0.0f;

public:
	void Init();
	void Update();
	void ViewSetting();
	void SetCameraZoomPos(Vector2 value, Vector2 zoomSize);
	void ShakeCamera(float time);

};

#define CAMERAMANAGER CameraManager::GetInstance()