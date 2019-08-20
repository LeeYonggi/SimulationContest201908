#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	Init();
}

ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Init()
{
	for (int i = 0; i <= GameObject::GAMEOBJECT_TAG::UI; i++)
		objectMap.insert(make_pair((GameObject::GAMEOBJECT_TAG)i, list<GameObject*>()));
}

void ObjectManager::Update()
{
	for (auto iter = objectMap.begin(); iter != objectMap.end(); iter++)
	{
		for (auto obj = iter->second.begin(); obj != iter->second.end(); )
		{
			if ((*obj)->destroy)
			{
				sortList.remove((*obj));

				SAFE_RELEASE((*obj));
				SAFE_DELETE((*obj));

				obj = iter->second.erase(obj);
			}
			else
			{
				if ((*obj)->active)
					(*obj)->Update();
				obj++;
			}
		}
	}
}

bool objSort(GameObject* obj1, GameObject* obj2)
{
	if (obj1->pos.z > obj2->pos.z)
		return true;
	if (obj1->pos.z == obj2->pos.z)
	{
		if (obj1->pos.y > obj2->pos.y)
			return true;
	}
	return false;
}
void ObjectManager::Render()
{
	sortList.sort(objSort);

	for (auto iter : sortList)
	{
		if (iter->active)
			iter->Render();
	}
}

void ObjectManager::Release()
{
	for (auto iter : objectMap)
	{
		for (auto obj : iter.second)
		{
			SAFE_RELEASE(obj);
			SAFE_DELETE(obj);
		}
		iter.second.clear();
	}
	objectMap.clear();
}

list<GameObject*> *ObjectManager::GetObjectList(GameObject::GAMEOBJECT_TAG tag)
{
	auto iter = objectMap.find(tag);
	if (iter == objectMap.end()) return nullptr;

	return &iter->second;
}
