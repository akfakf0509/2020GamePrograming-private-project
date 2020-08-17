#include "stdafx.h"
#include "Ingame.h"
#include "SpriteRenderer.h"
#include "Transform.h"

Ingame::Ingame() {
	background = CreateObject();

	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/background.png");

	background->GetComponent<Transform>()
		->SetAnchor(background->GetComponent<SpriteRenderer>()->GetTexture()->GetSize().width / 2, background->GetComponent<SpriteRenderer>()->GetTexture()->GetSize().height / 2);
}

Ingame::~Ingame() {
}