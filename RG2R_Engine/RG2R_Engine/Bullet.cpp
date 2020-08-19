#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() {

}

Bullet::~Bullet() {
}

float Bullet::GetSpeed() {
	return speed;
}

int Bullet::GetDamage()
{
	return damage;
}

Vec2F Bullet::GetDirection()
{
	return direction;
}

Bullet* Bullet::SetSpeed(float speed) {
	this->speed = speed;

	return this;
}

Bullet* Bullet::SetDameage(int damage)
{
	this->damage = damage;

	return this;
}

Bullet* Bullet::SetDirection(Vec2F direction)
{
	this->direction = direction;

	return this;
}
