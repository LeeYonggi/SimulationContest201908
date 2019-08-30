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
	map<string, LPD3DXEFFECT> shaderMap;
	map<pair<string, int>, LPD3DXFONT> fontMap;

public:
	void Init();
	void Release();


public:
	Texture* AddTexture(string path);
	vector<Texture*> AddAnimeTexture(string path, int low, int high);
	LPD3DXEFFECT CreateShader(string path);
	LPD3DXFONT CreateFontA(const string& faceName, int size);
	void CreateFontList(const string& faceName, int start_size, int end_size);
	LPD3DXFONT FindFont(const string& faceName, int size);
};

#define RESOURCEMANAGER ResourceManager::GetInstance()