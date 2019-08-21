/*
�Ʊ� ����Ʈ�� �� �� �׷��� ����Ʈ�� ����Ÿ�� �ؽ���.
*/
texture g_lightMapTex;
sampler2D g_lightMapSampler = sampler_state
{
	Texture = (g_lightMapTex);
};

/*
�þ� ��Ӱ� ���ִ� ������ �ؽ���.
*/
texture g_darkMapTex;
sampler2D g_darkMapSampler = sampler_state
{
	Texture = (g_darkMapTex);
};

float4 psMain(float2 uv : TEXCOORD) : COLOR0
{
	// output�� rgb�� ������ �ؽ��ĸ� ���󰡹Ƿ� �ϴ� ������ �ؽ����� uv ��ǥ�� �ִ� rgba�� �޾ƿ´�.
	// output�� ���İ��� �������� �����ٰŴ�.
	float4 output = tex2D(g_darkMapSampler, uv);

	/*
	���� output�� ����(output.a)�� g_darkMapSampler �ؽ��� uv�� ��ǥ�� �ִ� �ؼ��� ���İ��� �����Ƿ�
	output.a�� �־��൵ ����.
	*/
	float darkMapAlpha = output.a;
	/*
	tex2D�� �ؽ����� �ؼ�(�� �ؽ��� �ȼ��̶� �����ϼ�)�� �޾ƿ��� �ǵ�,
	ù ���ڴ� �޾ƿ� �ؽ��� ���÷�(�ؽ��ĸ� ���ø� �� ��ü.. �׳� �ؽ��Ķ� ���� �����ϴµ� �������),
	�� ��° ���ڴ� uv ��ǥ��.
	��, �ؽ��� ���÷��� uv ��ǥ�� �ִ� �ؼ�(rgba)�� �޾ƿ��� �Լ���.
	*/
	float lightMapAlpha = tex2D(g_lightMapSampler, uv).a;
	float finalAlpha = darkMapAlpha - lightMapAlpha;
	
	/*
	���İ� 0���� ���� ��� 0���� �������ش�.
	*/
	if (finalAlpha < 0)
		finalAlpha = 0;

	/*
	output.a�� �������ش�.
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