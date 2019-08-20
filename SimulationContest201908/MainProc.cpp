#include "DXUT.h"
#include "MainProc.h"

#include "IngameScene.h"

void MainProc::Init()
{
	SCENEMANAGER->AddScene(new IngameScene);
}

void MainProc::Update()
{
	OBJECTMANAGER->Update();

	SCENEMANAGER->Update();

	INPUTMANAGER->Update();
}

void MainProc::Render()
{
	CAMERAMANAGER->ViewSetting();

	OBJECTMANAGER->Render();

	SCENEMANAGER->Render();
}

void MainProc::Release()
{
	CameraManager::ReleaseInstance();
	RenderManager::ReleaseInstance();
	ObjectManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
	ResourceManager::ReleaseInstance();
	InputManager::ReleaseInstance();
	GameManager::ReleaseInstance();
}
