#include "stdafx.h"
#include "Enemy.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"

Enemy::Enemy() {
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

}

void Enemy::OnCollisionStay(CollisionInfo* collision) {
	std::cout << "Collision" << std::endl;
}