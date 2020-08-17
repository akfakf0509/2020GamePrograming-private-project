#pragma once
#include "Scene.h"
class Ingame :
	public Scene
{
private:
	Object* background;
public:
	Ingame();
	~Ingame();
};