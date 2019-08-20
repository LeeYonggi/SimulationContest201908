#include "DXUT.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
	Init();
}

CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{

}

void CameraManager::ViewSetting()
{
	if (isCameraZoom.first)
	{
		pos.x = Lerp(pos.x, cameraZoomPos.x, cameMoveSpeed);
		pos.y = Lerp(pos.y, cameraZoomPos.y, cameMoveSpeed);
		screenSize = Lerp(screenSize, zoomSize, cameMoveSpeed);
		if (Vec2Distance(Vector2(pos), cameraZoomPos) < 1.0f)
		{
			isCameraZoom.second = true;
			isCameraZoom.first = false;
		}
	}
	if (isCameraZoom.second)
	{
		pos.x = Lerp(pos.x, pastZoomPos.x, cameMoveSpeed);
		pos.y = Lerp(pos.y, pastZoomPos.y, cameMoveSpeed);
		screenSize = Lerp(screenSize, {640, 360}, cameMoveSpeed);
		if (Vec2Distance(Vector2(pos), pastZoomPos) < 10.0f)
		{
			isCameraZoom.second = false;
		}
	}
	at.x = pos.x;
	at.y = pos.y;
	Matrix mat, proj;
	D3DXMatrixLookAtLH(&mat, &pos, &at, &up);

	D3DXMatrixOrthoLH(&proj, screenSize.x, screenSize.y, 1, 10000.0f);

	DEVICE->SetTransform(D3DTS_VIEW, &mat);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void CameraManager::SetCameraZoomPos(Vector2 value, Vector2 zoomSize)
{
	cameraZoomPos = value;
	isCameraZoom.first = true;
	pastZoomPos = Vector2(pos);
	this->zoomSize = zoomSize;
}
