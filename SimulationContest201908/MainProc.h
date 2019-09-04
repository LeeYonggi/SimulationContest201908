#pragma once

struct Point
{
	Point()
		:x(0), y(0) {}

	int x;
	int y;
};
class MainProc
{
private:
	Texture* texture;

public:
	void Init();
	void Update();
	void Render();
	void Release();
};

