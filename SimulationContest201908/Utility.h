#pragma once


float RotateToVec2(Vector2 p1, Vector2 p2);

bool RectCollision(Vector2 p1, Vector2 size1, Vector2 p2, Vector2 size2);

Vector2 WorldToScreen(Vector2 p1);

float Vec2Distance(Vector2 p1, Vector2 p2);

int RandomNumber(int low, int high);

bool CircleCollision(Vector2 p1, float r1, Vector2 p2, float r2);

bool WallCollision(Vector2 p1, Vector2 _size);

template<typename T>
T Lerp(T p1, T p2, float d)
{
	return p1 + (p2 - p1) * d;
}

