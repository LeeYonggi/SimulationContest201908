#include "DXUT.h"
#include "RenderManager.h"

RenderManager::RenderManager()
{
	Init();
}

RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Init()
{
	float size = 0.5f;

	vertex.push_back(TexVertex({ size, size, 0 },	{ 1, 0 }));
	vertex.push_back(TexVertex({ size, -size, 0 },	{ 1, 1 }));
	vertex.push_back(TexVertex({ -size, -size, 0 },	{ 0, 1 }));
	vertex.push_back(TexVertex({ -size, -size, 0 }, { 0, 1 }));
	vertex.push_back(TexVertex({ -size, size, 0 },	{ 0, 0 }));
	vertex.push_back(TexVertex({ size, size, 0 },	{ 1, 0 }));

	xFlipvertex.push_back(TexVertex({ size, size, 0 }, { 0, 0 }));
	xFlipvertex.push_back(TexVertex({ size, -size, 0 }, { 0, 1 }));
	xFlipvertex.push_back(TexVertex({ -size, -size, 0 }, { 1, 1 }));
	xFlipvertex.push_back(TexVertex({ -size, -size, 0 }, { 1, 1 }));
	xFlipvertex.push_back(TexVertex({ -size, size, 0 }, { 1, 0 }));
	xFlipvertex.push_back(TexVertex({ size, size, 0 }, { 0, 0 }));

	yFlipvertex.push_back(TexVertex({ size, size, 0 }, { 1, 1 }));
	yFlipvertex.push_back(TexVertex({ size, -size, 0 }, { 1, 0 }));
	yFlipvertex.push_back(TexVertex({ -size, -size, 0 }, { 0, 0 }));
	yFlipvertex.push_back(TexVertex({ -size, -size, 0 }, { 0, 0 }));
	yFlipvertex.push_back(TexVertex({ -size, size, 0 }, { 0, 1 }));
	yFlipvertex.push_back(TexVertex({ size, size, 0 }, { 1, 1 }));

	D3DXCreateSprite(DEVICE, &sprite);
}

void RenderManager::Release()
{
	SAFE_RELEASE(sprite);
}

void RenderManager::DrawImage(Texture* texture, Vector3 pos, Vector2 scale, float rotate, Color color, pair<bool, bool> flip)
{
	Matrix matW, matS, matR, matT;

	D3DXMatrixScaling(&matS, scale.x * texture->info.Width, scale.y * texture->info.Height, 1);
	D3DXMatrixRotationZ(&matR, rotate);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);

	matW = matS * matR * matT;

	DEVICE->SetTransform(D3DTS_WORLD, &matW);

	DEVICE->SetRenderState(D3DRS_TEXTUREFACTOR, color);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	DEVICE->SetFVF(TexVertex::FVF);

	D3DMATERIAL9 mtl;
	mtl.Ambient = mtl.Diffuse = mtl.Emissive = mtl.Specular = color;

	DEVICE->SetMaterial(&mtl);

	DEVICE->SetTexture(0, texture->tex);

	if (flip.first)
	{
		DEVICE->DrawPrimitiveUP(
			D3DPT_TRIANGLELIST,
			xFlipvertex.size() / 3,
			&xFlipvertex[0],
			sizeof(TexVertex)
		);
	}
	else if (flip.second)
	{
		DEVICE->DrawPrimitiveUP(
			D3DPT_TRIANGLELIST,
			yFlipvertex.size() / 3,
			&yFlipvertex[0],
			sizeof(TexVertex)
		);
	}
	else
	{
		DEVICE->DrawPrimitiveUP(
			D3DPT_TRIANGLELIST,
			vertex.size() / 3,
			&vertex[0],
			sizeof(TexVertex)
		);
	}

	DEVICE->SetTexture(0, nullptr);
}

void RenderManager::DrawSprite(Texture* texture, Vector2 pos, Vector2 scale, float rotate, Color color)
{
	Matrix matW, matS, matR, matT;

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&matR, rotate);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->SetTransform(&matW);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	Vector3 center = { texture->info.Width * 0.5f, texture->info.Height * 0.5f, 0 };

	sprite->Draw(texture->tex, nullptr, &center, nullptr, color);
	sprite->End();
}

void RenderManager::DrawLine(Vector2 p1, Vector2 p2, float width, Color color)
{
	LPD3DXLINE line;

	D3DXCreateLine(DEVICE, &line);

	line->SetWidth(width);

	vector<Vector2> lineList;

	lineList.push_back(Vector2(p1.x, p1.y));
	lineList.push_back(Vector2(p2.x, p1.y));
	lineList.push_back(Vector2(p2.x, p2.y));
	lineList.push_back(Vector2(p1.x, p2.y));
	lineList.push_back(Vector2(p1.x, p1.y));

	line->Begin();

	line->Draw(&lineList[0], lineList.size(), color);

	line->End();
	line->Release();
}

void RenderManager::DrawLightShader(LPD3DXEFFECT shader, LPDIRECT3DTEXTURE9 lightMapTexture, LPDIRECT3DTEXTURE9 darkMapTexture)
{
	shader->SetTexture((D3DXHANDLE)"g_lightMapTex", lightMapTexture);
	shader->SetTexture((D3DXHANDLE)"g_darkMapTex", darkMapTexture);

	UINT numPasses = 0;
	shader->Begin(&numPasses, 0);
	for (UINT i = 0; i < numPasses; ++i)
	{
		Matrix matW;
		D3DXMatrixTranslation(&matW, SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0);
		sprite->SetTransform(&matW);
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		shader->BeginPass(i);
		Vector3 center = { SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0 };
		sprite->Draw(lightMapTexture, nullptr, &center, nullptr, Color(1, 1, 1, 1));

		shader->EndPass();

		sprite->End();
	}
	shader->End();
}
