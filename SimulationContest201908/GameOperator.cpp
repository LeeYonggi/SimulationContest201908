#include "DXUT.h"
#include "GameOperator.h"

#include "SBubble.h"

GameOperator::GameOperator()
	: UI(Vector2(SCREEN_X * 0.5f, SCREEN_Y * 0.5f), RESOURCEMANAGER->AddTexture("UI/op/operater_1.png"))
{
	pos = Vector3(1131, 654, -13);
}

GameOperator::~GameOperator()
{
	SAFE_DELETE(animator);
	GAMEMANAGER->oper = nullptr;
}

void GameOperator::Init()
{
	animator = new Animator(this);
	animator->AddAnime("Idle", new Animation(RESOURCEMANAGER->AddAnimeTexture("UI/op/operater_%d.png", 1, 1), true));
	animator->AddAnime("Talk", new Animation(RESOURCEMANAGER->AddAnimeTexture("UI/op/operater_%d.png", 1, 2), true));
	animator->GetAnime("Talk")->animeSpeed = 5.0f;
	animator->SetNowAnime("Talk");

	sbubble = OBJECTMANAGER->AddObject(GameObject::UI, new SBubble());
	sbubble->active = true;
	sbubble->SetAnime("Open");

	SpeechInit();
}

void GameOperator::Update()
{
	animator->Update();
	if (time > 50)
		CloseBubble();
	time += ELTime * textSpeed;
}

void GameOperator::Render()
{
	if (speechActive == true)
	{
		wstring str = speech[nowSpeech];
		str = str.substr(0, (int)min((int)time, str.size()));
		RENDERMANAGER->DrawFont(str, "���� ���", Vector2(300, 520), 35, color);
	}
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, rotate, color);
}

void GameOperator::Release()
{

}

void GameOperator::SpeechInit()
{
	switch (GAMEMANAGER->GetStage())
	{
	case STAGE_1:
		speech.push_back(L"����, �κ����� �λ꿪���� ħ���ϰ� �ִ� �����Դϴ�.\n �κ����� �ı��ϸ� �������ּ���.");
		break;
	case STAGE_2:
		
		break;
	case STAGE_3:
		break;
	default:
		break;
	}
}

void GameOperator::SpeechChange(int num)
{
	nowSpeech = num;
	time = 0;
	sbubble->SetAnime("Open");
	sbubble->active = true;
	speechActive = true;
}

void GameOperator::CloseBubble()
{
	sbubble->SetAnime("Close");
	speechActive = false;
}

