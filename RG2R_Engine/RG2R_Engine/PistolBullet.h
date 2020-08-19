#pragma once
#include "Bullet.h"

class CollisionInfo;

class PistolBullet :
	public Bullet
{
private:
	float speed;
	int damage;
	Vec2F direction;
public:
	PistolBullet();
	~PistolBullet();

	void OnUpdate();
	void OnCollisionStay(CollisionInfo*);

	float GetSpeed();
	int GetDamage();
	Vec2F GetDirection();

	PistolBullet* SetSpeed(float);
	PistolBullet* SetDameage(int);
	PistolBullet* SetDirection(Vec2F);
};

