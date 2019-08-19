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

public:
	void Init();
	void Update();
	void Render();
	void Release();

public:
	void AddScene(Scene *scene);

};

#define SCENEMANAGER SceneManager::GetInstance()