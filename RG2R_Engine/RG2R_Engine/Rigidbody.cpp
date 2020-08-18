#include "stdafx.h"
#include "Rigidbody.h"
#include "Engine.h"
#include "Transform.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "CollisionInfo.h"

Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update() {
	acceleration = acceleration - acceleration / calculation_speed;
	velocity = acceleration * RG2R_TimeM->GetDeltaTime();
	this->GetOwner()->GetComponent<Transform>()
		->SetPos(this->GetOwner()->GetComponent<Transform>()->GetPos() + velocity);

	std::vector<Object*> objList =  GetOwner()->GetScene()->FindObjectsCondition([=](Object* obj) ->bool {
		return obj == GetOwner() ? false : obj->GetIsEnable() && obj->GetComponent<Rigidbody>();
	});

	for (auto iter : objList) {
		auto itercirclecollider = iter->GetComponent<CircleCollider>();
		auto iterboxcollider = iter->GetComponent<BoxCollider>();

		auto ownercircleCollider = GetOwner()->GetComponent<CircleCollider>();
		auto ownerboxCollider = GetOwner()->GetComponent<BoxCollider>();

		if (GetOwner()->GetIsEnable() && iter != GetOwner() && (ownercircleCollider || ownerboxCollider)) {
			Transform *obj1_transform = iter->GetComponent<Transform>();
			Transform *obj2_transform = GetOwner()->GetComponent<Transform>();
			if (iterboxcollider && ownerboxCollider) {
				bool is_crash = 1;

				Vec2F a1(cos(obj1_transform->GetRot()), sin(obj1_transform->GetRot()));
				Vec2F a2(-sin(obj1_transform->GetRot()), cos(obj1_transform->GetRot()));
				Vec2F a3(cos(obj2_transform->GetRot()), sin(obj2_transform->GetRot()));
				Vec2F a4(-sin(obj2_transform->GetRot()), cos(obj2_transform->GetRot()));

				Vec2F l = obj1_transform->GetPos() - obj2_transform->GetPos();

				float r1, r2, r3, r4;

				r1 = iterboxcollider->GetWidthSize() * fabs(a1.Dot(a1));
				r2 = iterboxcollider->GetHeightSize() * fabs(a2.Dot(a1));
				r3 = ownerboxCollider->GetWidthSize() * fabs(a3.Dot(a1));
				r4 = ownerboxCollider->GetHeightSize() * fabs(a4.Dot(a1));
				if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a1)))
					is_crash = 0;

				r1 = iterboxcollider->GetWidthSize() * fabs(a1.Dot(a2));
				r2 = iterboxcollider->GetHeightSize() * fabs(a2.Dot(a2));
				r3 = ownerboxCollider->GetWidthSize() * fabs(a3.Dot(a2));
				r4 = ownerboxCollider->GetHeightSize() * fabs(a4.Dot(a2));
				if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a2)))
					is_crash = 0;

				r1 = iterboxcollider->GetWidthSize() * fabs(a1.Dot(a3));
				r2 = iterboxcollider->GetHeightSize() * fabs(a2.Dot(a3));
				r3 = ownerboxCollider->GetWidthSize() * fabs(a3.Dot(a3));
				r4 = ownerboxCollider->GetHeightSize() * fabs(a4.Dot(a3));
				if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a3)))
					is_crash = 0;

				r1 = iterboxcollider->GetWidthSize() * fabs(a1.Dot(a4));
				r2 = iterboxcollider->GetHeightSize() * fabs(a2.Dot(a4));
				r3 = ownerboxCollider->GetWidthSize() * fabs(a3.Dot(a4));
				r4 = ownerboxCollider->GetHeightSize() * fabs(a4.Dot(a4));
				if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a4)))
					is_crash = 0;

				if (is_crash) {
					CollisionInfo *collision = new CollisionInfo{ iter };

					if (isFirstCollision) {
						ApplyListener(GetOwner()->onCollisionEnterListener, collision);
						GetOwner()->OnCollisionEnter(collision);
						isFirstCollision = false;
					}
					else {
						ApplyListener(iter->onCollisionStayListener, collision);
						iter->OnCollisionStay(collision);
					}
				}
				else {
					CollisionInfo *collision = new CollisionInfo{ iter };

					ApplyListener(GetOwner()->onCollisionExitListener, collision);
					GetOwner()->OnCollisionExit(collision);
					isFirstCollision = true;
				}
			}
			else if (itercirclecollider && ownerboxCollider) {
				bool is_crash = true;

				Vec2F a1(cos(obj2_transform->GetRot()), sin(obj2_transform->GetRot()));
				Vec2F a2(-sin(obj2_transform->GetRot()), cos(obj2_transform->GetRot()));

				Vec2F l = obj1_transform->GetPos() - obj2_transform->GetPos();

				if (obj2_transform->GetPos().x - ownerboxCollider->GetWidthSize() <= obj1_transform->GetPos().x && obj1_transform->GetPos().x <= obj2_transform->GetPos().x + ownerboxCollider->GetWidthSize() ||
					obj2_transform->GetPos().y - ownerboxCollider->GetHeightSize() <= obj1_transform->GetPos().y && obj1_transform->GetPos().y <= obj2_transform->GetPos().y + ownerboxCollider->GetHeightSize()) {

					if (ownerboxCollider->GetWidthSize() + itercirclecollider->GetRad() <= fabs(l.Dot(a1))) {
						is_crash = false;
					}

					if (ownerboxCollider->GetHeightSize() + itercirclecollider->GetRad() <= fabs(l.Dot(a2))) {
						is_crash = false;
					}
				}
				else {
					if (obj1_transform->GetPos().x >= obj2_transform->GetPos().x) {
						if (obj1_transform->GetPos().y >= obj2_transform->GetPos().y) {
							Vec2F point(obj2_transform->GetPos().x + ownerboxCollider->GetWidthSize(), obj2_transform->GetPos().y + ownerboxCollider->GetHeightSize());

							if (itercirclecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
								is_crash = false;
							}
						}
						else {
							Vec2F point(obj2_transform->GetPos().x + ownerboxCollider->GetWidthSize(), obj2_transform->GetPos().y - ownerboxCollider->GetHeightSize());

							if (itercirclecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
								is_crash = false;
							}
						}
					}
					else {
						if (obj1_transform->GetPos().y >= obj2_transform->GetPos().y) {
							Vec2F point(obj2_transform->GetPos().x - ownerboxCollider->GetWidthSize(), obj2_transform->GetPos().y + ownerboxCollider->GetHeightSize());

							if (itercirclecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
								is_crash = false;
							}
						}
						else {
							Vec2F point(obj2_transform->GetPos().x - ownerboxCollider->GetWidthSize(), obj2_transform->GetPos().y - ownerboxCollider->GetHeightSize());

							if (itercirclecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
								is_crash = false;
							}
						}
					}
				}

				if (is_crash) {
					Vec2F crashline = obj1_transform->GetPos() - obj2_transform->GetPos();

					if (abs(crashline.x) > abs(crashline.y)) {
						crashline = a1;
					}
					else {
						crashline = a2;
					}

					CollisionInfo *collision = new CollisionInfo{ iter , crashline };

					if (isFirstCollision) {
						ApplyListener(GetOwner()->onCollisionEnterListener, collision);
						GetOwner()->OnCollisionEnter(collision);
						isFirstCollision = false;
					}
					else {
						ApplyListener(iter->onCollisionStayListener, collision);
						iter->OnCollisionStay(collision);
					}
				}
				else {
					Vec2F crashline = obj1_transform->GetPos() - obj2_transform->GetPos();

					if (abs(crashline.x) > abs(crashline.y)) {
						crashline = a1;
					}
					else {
						crashline = a2;
					}

					CollisionInfo *collision = new CollisionInfo{ iter , crashline };

					ApplyListener(GetOwner()->onCollisionExitListener, collision);
					GetOwner()->OnCollisionExit(collision);
					isFirstCollision = true;
				}
			}
			else if (itercirclecollider && ownercircleCollider) {
				Vec2F distance = obj1_transform->GetPos() - obj2_transform->GetPos();

				if (itercirclecollider->GetRad() + ownercircleCollider->GetRad() >= sqrt(pow(distance.x, 2) + pow(distance.y, 2))) {
					Vec2F crashline = distance.Normalize();
					CollisionInfo *collision = new CollisionInfo{ iter , crashline };

					if (isFirstCollision) {
						ApplyListener(GetOwner()->onCollisionEnterListener, collision);
						GetOwner()->OnCollisionEnter(collision);
						isFirstCollision = false;
					}
					else {
						ApplyListener(iter->onCollisionStayListener, collision);
						iter->OnCollisionStay(collision);
					}
				}
				else {
					Vec2F crashline(0, 0);
					CollisionInfo *collision = new CollisionInfo{ iter , crashline };
					ApplyListener(GetOwner()->onCollisionExitListener, collision);
					GetOwner()->OnCollisionExit(collision);
					isFirstCollision = true;
				}
			}
		}
	}
}

void Rigidbody::Render()
{
}

void Rigidbody::Render(ViewRenderData &)
{
}

Rigidbody* Rigidbody::SetForce(Vec2F _acceleration) {
	acceleration = _acceleration;

	return this;
}

Rigidbody* Rigidbody::SetForce(float _x, float _y) {
	acceleration = Vec2F(_x, _y);

	return this;
}

Rigidbody* Rigidbody::AddForce(Vec2F _acceleration) {
	acceleration += _acceleration;

	return this;
}

Rigidbody* Rigidbody::AddForce(float _x, float _y) {
	acceleration += Vec2F(_x, _y);

	return this;
}

Rigidbody* Rigidbody::SetCalculationSpeed(float _calculation_speed) {
	calculation_speed = _calculation_speed;

	return this;
}

Vec2F Rigidbody::GetForce() {
	return acceleration;
}

float Rigidbody::GetCalculationSpeed() {
	return calculation_speed;
}