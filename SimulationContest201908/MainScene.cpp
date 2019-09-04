#include "DXUT.h"
#include "MainScene.h"

#include "UI.h"
#include "IngameScene.h"

void ChangeIngame()
{
	SCENEMANAGER->AddScene(new IngameScene, true);
}

void MainScene::Init()
{
	startUi = new UI(Vector2(307, 470), RESOURCEMANAGER->AddTexture("main/start.png"));
	OBJECTMANAGER->AddObject(GameObject::OBJ_UI, startUi);
	startUi->SetPressOn(true);
	startUi->pos.z = -1;
	startUi->SetPointEnter(ChangeIngame);

	mainUi = new UI(Vector2(640, 360), RESOURCEMANAGER->AddTexture("main/background.png"));
	OBJECTMANAGER->AddObject(GameObject::OBJ_UI, mainUi);

	title = new UI(Vector2(350, 225), RESOURCEMANAGER->AddTexture("main/title.png"));
	OBJECTMANAGER->AddObject(GameObject::OBJ_UI, title);
}

void MainScene::Update()
{
}

void MainScene::Render()
{
}

void MainScene::Release()
{
}
