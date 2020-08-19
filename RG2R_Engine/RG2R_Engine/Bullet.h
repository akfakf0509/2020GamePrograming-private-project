#pragma once
#include "Object.h"
class Bullet :
	public Object
{
private:
	int damage;
public:
	Bullet();
	~Bullet();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Render(ViewRenderData&) = 0;

	virtual std::type_index GetID() { return typeid(Bullet); }
	static std::type_index GetFamilyID(void) { return typeid(Bullet); }

	   
};