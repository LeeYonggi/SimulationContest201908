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

	sbubble = OBJECTMANAGER->AddObject(GameObject::OBJ_UI, new SBubble());
	sbubble->active = true;
	sbubble->SetAnime("Open");

	SpeechInit();
}

void GameOperator::Update()
{
	animator->Update();
	if (speechActive == false) return;
	if (time > timeLimit[nowSpeech])
		CloseBubble();
	time += ELTime * textSpeed;
}

void GameOperator::Render()
{
	if (speechActive == true)
	{
		wstring str = speech[nowSpeech];
		str = str.substr(0, (int)min((int)time, str.size()));
		RENDERMANAGER->DrawFont(str, "맑은 고딕", Vector2(300, 520), 35, color);
	}
	RENDERMANAGER->DrawSprite(mainTexture, Vector2(pos), scale, { 1, 1 }, rotate, color);
}

void GameOperator::Release()
{

}

void GameOperator::SpeechInit()
{
	switch (GAMEMANAGER->GetStage())
	{
	case STAGE_1:
		speech.push_back(L"대장, 로봇들이 부산역까지 침공하고 있는 상태입니다.\n로봇들을 파괴하며 전진해주세요.");
		timeLimit.push_back(50);
		speech.push_back(L"대장, 로봇들이 얼마 남지 않았습니다.\n힘을 내요!");
		timeLimit.push_back(50);
		break;
	case STAGE_2:
		speech.push_back(L"로봇들이 앞 길거리를 점령하고 있는 상태입니다.\n로봇들을 파괴해 탈환당한 길거리를 되찾아 오세요.");
		timeLimit.push_back(65);

		break;
	case STAGE_3:
		break;
	default:
		break;
	}
}

void GameOperator::SpeechChange(int num)
{
	time = 0;
	sbubble->SetAnime("Open");
	sbubble->active = true;
	speechActive = true;
	animator->SetNowAnime("Talk");
	nowSpeech = num;
}

void GameOperator::CloseBubble()
{
	sbubble->SetAnime("Close");
	speechActive = false;
	animator->SetNowAnime("Idle");
}

