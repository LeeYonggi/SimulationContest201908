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

private:
	map<GameObject::GAMEOBJECT_TAG, list<GameObject*>> objectMap;
	list<GameObject*> sortList;

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