#pragma once
#include "UI.h"

class SBubble;
class GameOperator :
	public UI
{
public:
	GameOperator();
	virtual ~GameOperator();

private:
	Animator* animator = nullptr;
	vector<wstring> speech;
	SBubble* sbubble = nullptr;
	int nowSpeech = 0;
	float time = 0.0f;
	float textSpeed = 10.0f;
	bool speechActive = false;
	vector<float> timeLimit;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;


public:
	void SpeechInit();
	void SpeechChange(int num);
	void CloseBubble();
};
