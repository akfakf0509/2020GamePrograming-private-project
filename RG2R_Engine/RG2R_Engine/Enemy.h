#pragma once
#include "Object.h"
class Enemy :
	public Object
{
private:
public:
	Enemy();
	~Enemy();

	void OnUpdate();
	void OnCollisionStay(CollisionInfo*);
};

