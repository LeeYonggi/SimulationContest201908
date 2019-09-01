#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	Init();
}

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (nextScene)
	{
		SAFE_RELEASE(nowScene);
		SAFE_DELETE(nowScene);

		OBJECTMANAGER->Release();
		OBJECTMANAGER->Init();

		CAMERAMANAGER->isCameraZoom = make_pair(false, false);

		nextScene->Init();

		nowScene = nextScene;
		nextScene = nullptr;
	}
	nowScene->Update();
}

void SceneManager::Render()
{
	nowScene->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_DELETE(nowScene);

	SAFE_RELEASE(nextScene);
	SAFE_DELETE(nextScene);
}

void SceneManager::AddScene(Scene* scene)
{
	nextScene = scene;
}
