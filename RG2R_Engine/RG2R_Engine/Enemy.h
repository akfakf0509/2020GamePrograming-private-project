#pragma once
#include "Object.h"

class Enemy :
	public Object
{
private:
	Object* target;
public:
	Enemy();
	~Enemy();

	void OnUpdate();
	void OnCollisionStay(CollisionInfo*);

	void SetTarget(Object*);
};

