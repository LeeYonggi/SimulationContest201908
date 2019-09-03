#pragma once
#include "Singleton.h"
class SceneManager :
	public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

private:
	Scene* nextScene = nullptr;
	Scene* nowScene = nullptr;
	bool isChangeEffect = false;
	float time = 0.0f;
	vector<Texture*> sceneTexture;

public:
	void Init();
	void Update();
	void Render();
	void Release();

private:
	void SceneChange();

public:
	void AddScene(Scene *scene, bool isSceneEffect = false);

};

#define SCENEMANAGER SceneManager::GetInstance()