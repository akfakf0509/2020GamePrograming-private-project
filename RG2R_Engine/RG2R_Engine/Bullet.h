#pragma once
#include "Object.h"
class Bullet :
	public Object
{
private:
	float speed;
	int damage;
	Vec2F direction;
public:
	Bullet();
	~Bullet();

	float GetSpeed();
	int GetDamage();
	Vec2F GetDirection();

	Bullet* SetSpeed(float);
	Bullet* SetDameage(int);
	Bullet* SetDirection(Vec2F);
};