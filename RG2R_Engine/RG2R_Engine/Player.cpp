#include "stdafx.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Engine.h"
#include "Transform.h"

Player::Player() {
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
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KEYSTATE_STAY) {
		GetComponent<Transform>()
			->SetPos(GetComponent<Transform>()->GetPos() + Vec2F(0, 0.01f));
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KEYSTATE_STAY) {
		GetComponent<Transform>()
			->SetPos(GetComponent<Transform>()->GetPos() + Vec2F(0, -0.01f));
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KEYSTATE_STAY) {
		GetComponent<Transform>()
			->SetPos(GetComponent<Transform>()->GetPos() + Vec2F(-0.01f, 0));
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KEYSTATE_STAY) {
		GetComponent<Transform>()
			->SetPos(GetComponent<Transform>()->GetPos() + Vec2F(0.01f, 0));
	}
}

void Player::OnCollisionStay(CollisionInfo* collision) {
	std::cout << "Collision" << std::endl;
}