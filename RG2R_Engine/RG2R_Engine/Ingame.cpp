#include "stdafx.h"
#include "Ingame.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Player.h"
#include "Enemy.h"

Ingame::Ingame() {
	background = CreateObject();

	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Background.png");

	background->GetComponent<Transform>()
		->SetAnchor(background->GetComponent<SpriteRenderer>()->GetTexture()->GetSize().width / 2, background->GetComponent<SpriteRenderer>()->GetTexture()->GetSize().height / 2);

	player = new Player();
	AttachObject(player);

	enemy = new Enemy();
	AttachObject(enemy);
}

Ingame::~Ingame() {
}