#pragma once
#include "Singleton.h"

struct Texture
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
};

class ResourceManager :
	public Singleton<ResourceManager>
{
public:
	ResourceManager();
	virtual ~ResourceManager();

private:
	map<string, Texture*> textureMap;

public:
	void Init();
	void Release();


public:
	Texture* AddTexture(string path);
	vector<Texture*> AddAnimeTexture(string path, int low, int high);
};

#define RESOURCEMANAGER ResourceManager::GetInstance()