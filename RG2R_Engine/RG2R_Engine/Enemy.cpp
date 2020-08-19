#include "stdafx.h"
#include "Enemy.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Player.h"

Enemy::Enemy() {
	GetComponent<Transform>()
		->SetAnchor(16, 16);
	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Enemy.png");
	AttachComponent<BoxCollider>()
		->SetWidthSize(0.25f)
		->SetHeightSize(0.25f);
	AttachComponent<Rigidbody>();
}

Enemy::~Enemy() {
}

void Enemy::OnUpdate() {
	if (target) {
		Vec2F target_direction = target->GetComponent<Transform>()->GetPos() - GetComponent<Transform>()->GetPos();

		target_direction = target_direction.Normalize();

		GetComponent<Transform>()->Translate(target_direction * 0.01f);

		std::cout << "target_direction" << target_direction.x << " " << target_direction.y << std::endl;
		std::cout << "Pos : " << GetComponent<Transform>()->GetPos().x << " " << GetComponent<Transform>()->GetPos().y << std::endl;
	}
}

void Enemy::OnCollisionStay(CollisionInfo* collision) {
	std::cout << "Collision" << std::endl;
}

int Enemy::GetHp()
{
	return hp;
}

Enemy* Enemy::SetTarget(Object* target) {
	this->target = target;
}

Enemy * Enemy::SetHp(int hp)
{
	this->hp = hp;

	return this;
}
