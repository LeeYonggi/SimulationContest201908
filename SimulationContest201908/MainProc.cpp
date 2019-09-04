#include "DXUT.h"
#include "MainProc.h"

#include "IngameScene.h"
#include "MainScene.h"

void MainProc::Init()
{
	SCENEMANAGER->AddScene(new MainScene, false);
}

void MainProc::Update()
{
	SCENEMANAGER->Update();

	OBJECTMANAGER->Update();

	INPUTMANAGER->Update();

	CAMERAMANAGER->Update();
}

void MainProc::Render()
{
	CAMERAMANAGER->ViewSetting();

	OBJECTMANAGER->Render();

	SCENEMANAGER->Render();

	INPUTMANAGER->Render();
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
