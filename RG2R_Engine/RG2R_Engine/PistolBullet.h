#pragma once
#include "Bullet.h"
class PistolBullet :
	public Bullet
{
private:
public:
	PistolBullet();
	~PistolBullet();

	void Update();

	std::type_index GetID() { return typeid(PistolBullet); }
	static std::type_index GetFamilyID(void) { return typeid(PistolBullet); }
};

