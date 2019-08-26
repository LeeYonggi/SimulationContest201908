#pragma once
#include "Singleton.h"

struct TexVertex
{
	Vector3 pos;
	Vector2 uv;

	enum { FVF = (D3DFVF_XYZ | D3DFVF_TEX1 ) };
	TexVertex() { }
	TexVertex(Vector3 _pos, Vector2 _uv)
		: pos(_pos), uv(_uv) { }
};

class RenderManager :
	public Singleton<RenderManager>
{
public:
	RenderManager();
	virtual ~RenderManager();

private:
	vector<TexVertex> vertex;
	vector<TexVertex> xFlipvertex;
	vector<TexVertex> yFlipvertex;

	LPD3DXSPRITE sprite;

public:
	void Init();
	void Release();

public:
	void DrawImage(Texture* texture, Vector3 pos, Vector2 scale = { 1, 1 },
		float rotate = 0, Color color = { 1, 1, 1, 1 }, pair<bool, bool> flip = make_pair(false, false));
	void DrawSprite(Texture* texture, Vector2 pos, Vector2 scale = { 1, 1 },
		float rotate = 0, Color color = {1, 1, 1, 1});
	void DrawLine(Vector2 p1, Vector2 p2, float width, Color color = { 1, 1, 1, 1 });
	void DrawLightShader(LPD3DXEFFECT shader, LPDIRECT3DTEXTURE9 lightMapTexture,
		LPDIRECT3DTEXTURE9 darkMapTexture);
	void DrawFont(string str, Vector2 pos, float scale, D3DXCOLOR color = { 1, 1, 1, 1 });
};

#define RENDERMANAGER RenderManager::GetInstance()