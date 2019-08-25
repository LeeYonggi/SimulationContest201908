#pragma once
#include "Singleton.h"
class ObjectManager :
	public Singleton<ObjectManager>
{
public:
	ObjectManager();
	virtual ~ObjectManager();
public:
	void Init();
	void Update();
	void Render();
	void Release();

public:
	void LightingMapRender(float alpha);

private:
	map<GameObject::GAMEOBJECT_TAG, list<GameObject*>> objectMap;
	list<GameObject*> sortList;

private:
	Texture* darkTexture = nullptr;
	LPDIRECT3DSURFACE9 lightMapSurface = nullptr;
	LPDIRECT3DTEXTURE9 lightMapTexture = nullptr;

	LPDIRECT3DSURFACE9 darkMapSurface = nullptr;
	LPDIRECT3DTEXTURE9 darkMapTexture = nullptr;

	LPD3DXEFFECT lightShader = nullptr;

private:
	void CreateRenderTarget(LPDIRECT3DTEXTURE9 &rtTex, LPDIRECT3DSURFACE9 &rtSurf);
	void DrawTagObject(GameObject::GAMEOBJECT_TAG tag);

public:
	list<GameObject*> *GetObjectList(GameObject::GAMEOBJECT_TAG tag);

public:
	template<typename T>
	T* AddObject(GameObject::GAMEOBJECT_TAG tag, T *obj)
	{
		auto iter = objectMap.find(tag);

		iter->second.push_back(obj);

		obj->Init();
		obj->tag = tag;
		sortList.push_back(obj);

		return obj;
	}
};

#define OBJECTMANAGER ObjectManager::GetInstance()