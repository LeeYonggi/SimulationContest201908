#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void Init()		= 0;
	virtual void Update()	= 0;
	virtual void Render()	= 0;
	virtual void Release()	= 0;
	
public:
	enum GAMEOBJECT_TAG
	{
		BACKGROUND1,
		BACKGROUND2,
		PLAYER,
		ENEMY,
		GUN,
		PLAYER_BULLET,
		ENEMY_BULLET,
		EFFECT,
		UI,
		MOUSE_CONTROLL,
		END
	};

public:
	Vector3 pos = { 0, 0, 0 };
	Vector2 scale = { 1, 1 };
	float rotate = 0.0f;
	GAMEOBJECT_TAG tag;
	bool active = true;
	bool destroy = false;
	Texture* mainTexture = nullptr;
	Color color = {1, 1, 1, 1};
	pair<bool, bool> flip = make_pair(false, false);
	float radius = 5.0f;
	Texture* lightTexture = nullptr;

};

