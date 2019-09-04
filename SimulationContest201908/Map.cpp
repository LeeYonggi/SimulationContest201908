#include "DXUT.h"
#include "Map.h"

#include "Building.h"

Map *Map::nowMap = nullptr;

Map::Map()
{
	if (nowMap == nullptr)
		nowMap = this;
}

Map::~Map()
{
	if (nowMap == this)
		nowMap = nullptr;
}

void Map::Init()
{
	pos = { 0, 0, 800 };

	animator = new Animator(this);
	Animation* anime;

	Building* building = nullptr;

	switch (GAMEMANAGER->GetStage())
	{
	case STAGE_1:
		anime = new Animation(RESOURCEMANAGER->AddAnimeTexture("Map/Map1/Map/wave%d.png", 1, 5), true);
		anime->animeSpeed = 7;

		animator->AddAnime("Idle", anime);
		animator->SetNowAnime("Idle");

		mainTexture = RESOURCEMANAGER->AddTexture("Map/Map1/Map/wave1.png");
		
		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_1.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 0, 400, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -500, 450, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -500, 250, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -300, 450, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -300, 250, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 450, 450, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 450, 250, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/parasol_1.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -400, -150, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/parasol_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 450, -150, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/guardrail_1.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -240, 485, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/guardrail_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 550, 485, 0 };

		break;

	case STAGE_2:
		mainTexture = RESOURCEMANAGER->AddTexture("Map/Map2/map_2.png");

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map2/pojang_1.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -400, 200, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map2/pojang_2.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { -400, 0, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map2/pojang_3.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 400, 200, 0 };

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map2/pojang_4.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 400, 0, 0 };

		for (int i = 0; i < 3; i++)
		{
			building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
			OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
			building->pos = { -640 + i * 180.0f, 640, 0 };
		}
		for (int i = 0; i < 3; i++)
		{
			building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
			OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
			building->pos = { 300 + i * 180.0f, 640, 0 };
		}
		for (int i = 0; i < 3; i++)
		{
			building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
			OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
			building->pos = { -640 + i * 180.0f, -460, 0 };

			building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
			OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
			building->pos = { -640 + i * 180.0f, -640, 0 };
		}
		for (int i = 0; i < 3; i++)
		{
			building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
			OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
			building->pos = { 300 + i * 180.0f, -460, 0 };

			building = new Building(RESOURCEMANAGER->AddTexture("Map/Map1/tower_2.png"));
			OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
			building->pos = { 300 + i * 180.0f, -640, 0 };
		}
		break;
	case STAGE_3:
		mainTexture = RESOURCEMANAGER->AddTexture("Map/Map3/map_3.png");

		building = new Building(RESOURCEMANAGER->AddTexture("Map/Map3/station.png"));
		OBJECTMANAGER->AddObject(GameObject::BACKGROUND2, building);
		building->pos = { 0, 490, 0 };
		break;
	default:
		break;
	}
}

void Map::Update()
{
	animator->Update();
}

void Map::Render()
{
	RENDERMANAGER->DrawImage(mainTexture, pos, scale, rotate, color);
}

void Map::Release()
{
	SAFE_DELETE(animator);
}
