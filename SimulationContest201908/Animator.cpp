#include "DXUT.h"
#include "Animator.h"


Animator::~Animator()
{
	for (auto iter : animationMap)
	{
		SAFE_DELETE(iter.second);
	}
	animationMap.clear();
}

void Animator::AddAnime(string animeName, Animation *anime)
{
	animationMap.insert(make_pair(animeName, anime));
}

void Animator::SetNowAnime(string name)
{
	nowAnime = name;
	isEnd = false;
	frame = 0.0f;
}

void Animator::Update()
{
	auto iter = animationMap.find(nowAnime);

	if (iter == animationMap.end()) return;

	if (iter->second->isLoop)
	{
		int nowImage = (int)frame % iter->second->textures.size();
		obj->mainTexture = iter->second->textures[nowImage];
	}
	else
	{
		if (frame >= iter->second->textures.size())
		{
			frame = iter->second->textures.size() - 1;
			isEnd = true;
		}
		obj->mainTexture = iter->second->textures[(int)frame];
	}
	frame += ELTime * iter->second->animeSpeed;
}
