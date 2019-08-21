/*
아까 라이트들 싹 다 그려둔 라이트맵 렌더타겟 텍스쳐.
*/
texture g_lightMapTex;
sampler2D g_lightMapSampler = sampler_state
{
	Texture = (g_lightMapTex);
};

/*
시야 어둡게 해주는 검정색 텍스쳐.
*/
texture g_darkMapTex;
sampler2D g_darkMapSampler = sampler_state
{
	Texture = (g_darkMapTex);
};

float4 psMain(float2 uv : TEXCOORD) : COLOR0
{
	// output의 rgb는 검정색 텍스쳐를 따라가므로 일단 검정색 텍스쳐의 uv 좌표상에 있는 rgba를 받아온다.
	// output의 알파값은 마지막에 정해줄거다.
	float4 output = tex2D(g_darkMapSampler, uv);

	/*
	현재 output의 알파(output.a)는 g_darkMapSampler 텍스쳐 uv의 좌표에 있는 텍셀의 알파값과 같으므로
	output.a를 넣어줘도 좋다.
	*/
	float darkMapAlpha = output.a;
	/*
	tex2D는 텍스쳐의 텍셀(걍 텍스쳐 픽셀이라 생각하셈)을 받아오는 건데,
	첫 인자는 받아올 텍스쳐 샘플러(텍스쳐를 샘플링 한 객체.. 그냥 텍스쳐라 봐도 이해하는덴 지장없음),
	두 번째 인자는 uv 좌표다.
	즉, 텍스쳐 샘플러의 uv 좌표에 있는 텍셀(rgba)을 받아오는 함수다.
	*/
	float lightMapAlpha = tex2D(g_lightMapSampler, uv).a;
	float finalAlpha = darkMapAlpha - lightMapAlpha;
	
	/*
	알파가 0보다 작은 경우 0으로 보정해준다.
	*/
	if (finalAlpha < 0)
		finalAlpha = 0;

	/*
	output.a에 대입해준다.
	*/
	output.a = finalAlpha;

	return output;
}

technique t0
{
	pass p0
	{
		AlphaBlendEnable = TRUE;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		PixelShader = compile ps_2_0 psMain();
	}
}