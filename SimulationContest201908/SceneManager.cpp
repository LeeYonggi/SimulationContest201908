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
	sceneTexture = RESOURCEMANAGER->AddAnimeTexture("scene/scene_%d.png", 1, 17);
}

void SceneManager::Update()
{
	if (nextScene)
	{
		SceneChange();
	}
	if (isChangeEffect)
	{
		time += 0.2f;
		if (time > sceneTexture.size() - 1)
		{
			isChangeEffect = false;
		}
		if ((int)time == (int)(sceneTexture.size() / 2) && nextScene)
		{
			SceneChange();
		}
	}
	if(nowScene)
		nowScene->Update();
}

void SceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
	if(isChangeEffect)
		RENDERMANAGER->DrawSprite(sceneTexture[int(time)], Vector2(640, 360));
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_DELETE(nowScene);

	SAFE_RELEASE(nextScene);
	SAFE_DELETE(nextScene);
}

void SceneManager::SceneChange()
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

void SceneManager::AddScene(Scene* scene, bool isSceneEffect)
{
	nextScene = scene;
	isChangeEffect = isSceneEffect;
}
