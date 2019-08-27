#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	Init();

	darkTexture = RESOURCEMANAGER->AddTexture("Light/dark.png");

	CreateRenderTarget(lightMapTexture, lightMapSurface);
	CreateRenderTarget(darkMapTexture, darkMapSurface);

	lightShader = RESOURCEMANAGER->CreateShader("Shader/mask.fx");
}

ObjectManager::~ObjectManager()
{
	Release();

	SAFE_RELEASE(lightMapTexture);
	SAFE_RELEASE(darkMapTexture);
	SAFE_RELEASE(lightMapSurface);
	SAFE_RELEASE(darkMapSurface);
}

void ObjectManager::Init()
{
	for (int i = 0; i <= GameObject::GAMEOBJECT_TAG::END; i++)
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

	list<GameObject*> uiList;
	for (auto iter : sortList)
	{
		if (iter->tag == GameObject::UI || iter->tag == GameObject::MOUSE_CONTROLL)
		{
			uiList.push_back(iter);
			continue;
		}
		if (iter->active && iter->renderActive)
			iter->Render();
	}

	LightingMapRender(0.9);

	for (auto iter : uiList)
	{
		if (iter->active && iter->renderActive)
			iter->Render();
	}
	uiList.clear();
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

void ObjectManager::LightingMapRender(float alpha)
{
	LPDIRECT3DSURFACE9 backBufferSurface = nullptr;

	DEVICE->GetRenderTarget(0, &backBufferSurface);

	DEVICE->SetRenderTarget(0, lightMapSurface);

	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(0, 0, 0, 0), 1, 0);

	DrawTagObject(GameObject::PLAYER);
	DrawTagObject(GameObject::PLAYER_BULLET);
	DrawTagObject(GameObject::ENEMY_BULLET);
	
	DEVICE->SetRenderTarget(0, darkMapSurface);

	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(0, 0, 0, 0), 1, 0);

	RENDERMANAGER->DrawSprite(darkTexture, { (float)SCREEN_X * 0.5f, (float)SCREEN_Y * 0.5f },
		{1, 1}, 0, Color(1, 1, 1, alpha));

	DEVICE->SetRenderTarget(0, backBufferSurface);

	SAFE_RELEASE(backBufferSurface);

	RENDERMANAGER->DrawLightShader(lightShader, lightMapTexture, darkMapTexture);
}

void ObjectManager::CreateRenderTarget(LPDIRECT3DTEXTURE9& rtTex, LPDIRECT3DSURFACE9& rtSurf)
{
	DEVICE->CreateTexture(SCREEN_X, SCREEN_Y, 
		1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &rtTex, 0);

	rtTex->GetSurfaceLevel(0, &rtSurf);
}

void ObjectManager::DrawTagObject(GameObject::GAMEOBJECT_TAG tag)
{
	auto iter = GetObjectList(tag);

	for (auto obj : *iter)
	{
		if (!obj->lightTexture) continue;
		Texture* light = obj->lightTexture;
		RENDERMANAGER->DrawImage(light, obj->pos);
	}
}

list<GameObject*> *ObjectManager::GetObjectList(GameObject::GAMEOBJECT_TAG tag)
{
	auto iter = objectMap.find(tag);
	if (iter == objectMap.end()) return nullptr;

	return &iter->second;
}
