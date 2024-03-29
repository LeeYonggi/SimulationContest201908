#pragma once
#include "UI.h"
class SBubble :
	public UI
{
public:
	SBubble();
	virtual ~SBubble();

private:
	Animator* animator = nullptr;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetAnime(string str) 
	{
		animator->SetNowAnime(str); 
		animator->SetNowFrame(0);
	}
};

