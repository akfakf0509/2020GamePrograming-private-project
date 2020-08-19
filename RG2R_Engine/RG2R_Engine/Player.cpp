#include "stdafx.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Engine.h"
#include "Transform.h"

Player::Player() {
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

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KEYSTATE_STAY) {
		movement.y += 1;
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KEYSTATE_STAY) {
		movement.y -= 1;
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KEYSTATE_STAY) {
		movement.x -= 1;
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KEYSTATE_STAY) {
		movement.x += 1;
	}

	movement = movement.Normalize();

	GetComponent<Transform>()
		->Translate(movement * 0.02f)
		->LookAt(RG2R_InputM->FromUIToWorld(RG2R_InputM->GetMousePos()));
}

void Player::OnCollisionStay(CollisionInfo* collision) {
	std::cout << "Collision" << std::endl;
}