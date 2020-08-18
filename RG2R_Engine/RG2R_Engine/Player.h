#pragma once
#include "Object.h"
class Player :
	public Object
{
private:
public:
	Player();
	~Player();

	void OnUpdate();
	void OnCollisionStay(CollisionInfo*);
};

