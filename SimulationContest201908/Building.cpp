#include "DXUT.h"
#include "Building.h"

Building::Building(Texture* texture)
{
	mainTexture = texture;
}

Building::~Building()
{
}

void Building::Init()
{
	
}

void Building::Update()
{
	isCollisionCharacter = CharacterCollisionCheck(OBJECTMANAGER->GetObjectList(PLAYER));
	isCollisionCharacter = isCollisionCharacter || CharacterCollisionCheck(OBJECTMANAGER->GetObjectList(ENEMY));
}

void Building::Render()
{
	if (isCollisionCharacter)
		color.a = 0.5f;
	else
		color.a = 1.0f;

	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color);
}

void Building::Release()
{
}

bool Building::CharacterCollisionCheck(list<GameObject*>* objList)
{
	Vector2 size;
	size.x = mainTexture->info.Width;
	size.y = mainTexture->info.Height;

	for (auto obj : *objList)
	{
		Vector2 temp;
		temp.x = obj->mainTexture->info.Width;
		temp.y = obj->mainTexture->info.Height;
		if (RectCollision(Vector2(obj->pos), temp, Vector2(pos), size)
			&& pos.y < obj->pos.y)
		{
			return true;
		}
	}
	return false;
}
