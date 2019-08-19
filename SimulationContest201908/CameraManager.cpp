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
	Matrix mat, proj;
	D3DXMatrixLookAtLH(&mat, &pos, &at, &up);

	D3DXMatrixOrthoLH(&proj, screenSize.x, screenSize.y, 1, 10000.0f);

	DEVICE->SetTransform(D3DTS_VIEW, &mat);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}
