#pragma once
#include "GameObject.h"
class Building :
	public GameObject
{
public:
	Building(Texture *texture);
	virtual ~Building();
private:
	Texture* noAlphaTexture;
	Texture* alphaTexture;
	bool isCollisionCharacter = false;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	bool CharacterCollisionCheck(list<GameObject*> *objList);

};

