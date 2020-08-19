#include "stdafx.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Engine.h"
#include "Transform.h"
#include "PistolBullet.h"
#include "CollisionInfo.h"

Player::Player() {
	SetTag("Player");

	GetComponent<Transform>()
		->SetAnchor(16, 16);
	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Player.png");
	AttachComponent<BoxCollider>()
		->SetWidthSize(0.25f)
		->SetHeightSize(0.25f);
	AttachComponent<Rigidbody>();
}

Player::~Player() {
}

void Player::OnUpdate() {
	Vec2F movement(0,0);

	auto pos = GetComponent<Transform>()->GetPos();

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KEYSTATE_STAY && pos.y < 2.5f) {
		movement.y += 1;
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KEYSTATE_STAY && pos.y > -2.5) {
		movement.y -= 1;
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KEYSTATE_STAY && pos.x > -5) {
		movement.x -= 1;
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KEYSTATE_STAY && pos.x < 5) {
		movement.x += 1;
	}

	movement = movement.Normalize();

	GetComponent<Transform>()
		->Translate(movement * 0.02f)
		->LookAt(RG2R_InputM->FromUIToWorld(RG2R_InputM->GetMousePos()));
}

void Player::OnCollisionStay(CollisionInfo* collision) {
	if (collision->object->GetTag() == "Enemy") {
		SetIsEnable(false);
	}
}

Player* Player::Shoot() {
	if (GetIsEnable()){
		auto bullet = new PistolBullet();

	bullet->GetComponent<Transform>()
		->SetPos(GetComponent<Transform>()->GetPos())
		->SetRotation(GetComponent<Transform>()->GetRotation());
	bullet->SetDirection((RG2R_InputM->FromUIToWorld(RG2R_InputM->GetMousePos()) - GetComponent<Transform>()->GetPos()).Normalize());

	GetComponent<Transform>()->Translate((RG2R_InputM->FromUIToWorld(RG2R_InputM->GetMousePos()) - GetComponent<Transform>()->GetPos()).Normalize() * -0.1f);

	GetScene()->AttachObject(bullet);
	}
	return this;
}