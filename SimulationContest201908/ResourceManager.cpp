#include "DXUT.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	Init();
}

ResourceManager::~ResourceManager()
{
	Release();
}

void ResourceManager::Init()
{
}

void ResourceManager::Release()
{
	for (auto iter : textureMap)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	textureMap.clear();
	for (auto iter : shaderMap)
	{
		SAFE_RELEASE(iter.second);
	}
	shaderMap.clear();
}

Texture* ResourceManager::AddTexture(string path)
{
	auto iter = textureMap.find(path);
	if (iter != textureMap.end()) return iter->second;

	Texture* texture = new Texture;
	string str = "./Resources/" + path;

	D3DXCreateTextureFromFileExA(
		DEVICE,
		str.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0,
		&texture->info,
		nullptr,
		&texture->tex
	);

	textureMap.insert(make_pair(path, texture));

	return texture;
}

vector<Texture*> ResourceManager::AddAnimeTexture(string path, int low, int high)
{
	vector<Texture*> temp;
	for (int i = low; i <= high; i++)
	{
		CHAR ctr[128];

		sprintf(ctr, path.c_str(), i);
		temp.push_back(AddTexture(ctr));
	}
	return temp;
}

LPD3DXEFFECT ResourceManager::CreateShader(string path)
{
	auto iter = shaderMap.find(path);
	if (iter != shaderMap.end()) return iter->second;

	LPD3DXBUFFER err = nullptr;
	LPD3DXEFFECT shader = nullptr;

	string str = "./Resources/" + path;
	
	D3DXCreateEffectFromFileA(DEVICE, str.c_str(), NULL, NULL, D3DXSHADER_DEBUG,
		0, &shader, &err);

	if (err)
		MessageBoxA(DXUTGetHWND(), (LPCSTR)err->GetBufferPointer(), 0, 0);

	shaderMap.insert(make_pair(path, shader));

	return shader;
}
