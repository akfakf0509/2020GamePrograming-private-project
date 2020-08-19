#include "stdafx.h"
#include "PistolBullet.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CollisionInfo.h"
#include "BoxCollider.h"
#include "Rigidbody.h"

PistolBullet::PistolBullet()
{
	SetTag("Bullet");

	damage = 1;
	speed = 0.1f;
	direction = Vec2F(0, 0);

	GetComponent<Transform>()
		->SetAnchor(2, 4);
	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Bullet.png");
	AttachComponent<BoxCollider>()
		->SetWidthSize(0.25f / 8)
		->SetHeightSize(1);
	AttachComponent<Rigidbody>();
}

PistolBullet::~PistolBullet()
{
}

void PistolBullet::OnUpdate()
{
	GetComponent<Transform>()->Translate(direction * speed);

	auto pos = GetComponent<Transform>()->GetPos();

	if (-6 > pos.x || pos.x > 6 || -3 > pos.y || pos.y > 3) {
		Destroy();
	}
}

void PistolBullet::OnCollisionStay(CollisionInfo* collision) {
	if (collision->object->GetTag() == "Enemy") {
		collision->object->SetIsEnable(false);
		SetIsEnable(false);
	}
}

float PistolBullet::GetSpeed() {
	return speed;
}

int PistolBullet::GetDamage() {
	return damage;
}

Vec2F PistolBullet::GetDirection() {
	return direction;
}

PistolBullet* PistolBullet::SetSpeed(float speed) {
	this->speed = speed;

	return this;
}

PistolBullet* PistolBullet::SetDameage(int damage) {
	this->damage = damage;

	return this;
}

PistolBullet* PistolBullet::SetDirection(Vec2F direction) {
	this->direction = direction;

	return this;
}