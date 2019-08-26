#pragma once

struct Animation
{
	vector<Texture*> textures;
	bool isLoop = true;
	float animeSpeed = 10.0f;

	Animation(vector<Texture*> _textures, bool _isLoop)
		: textures(_textures), isLoop(_isLoop) { }
};

class GameObject;
class Animator
{
public:
	Animator(GameObject *_obj)
		: obj(_obj) { }
	virtual ~Animator();

private:
	map<string, Animation*> animationMap;
	string nowAnime = "NONE";
	GameObject* obj = nullptr;
	float frame = 0.0f;
	bool isEnd = false;

public:
	void AddAnime(string animeName, Animation *anime);
	void SetNowAnime(string name);
	Animation* GetNowAnime() { return animationMap[nowAnime]; }
	Animation* GetAnime(string str) { return animationMap[str]; }
	string GetNowAnimeName() { return nowAnime; }
	float GetNowFrame() { return frame; }
	void SetNowFrame(float value) { frame = value; }
	void Update();

public:
	bool GetFrameEnd() {return isEnd;}

};

