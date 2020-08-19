#pragma once
#include "Scene.h"

class Enemy;
class Player;

class Ingame :
	public Scene
{
private:
	Object* background;
	Player* player;
	Enemy* enemy;
public:
	Ingame();
	~Ingame();

	void OnUpdate();
};