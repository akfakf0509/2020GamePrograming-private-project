#pragma once
#include "Scene.h"
class Ingame :
	public Scene
{
private:
	Object* background;
	Object* player;
	Object* enemy;
public:
	Ingame();
	~Ingame();
};