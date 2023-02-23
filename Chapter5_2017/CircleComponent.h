#pragma once
#include "Component.h"
#include "Math.h"
#include "Actor.h"

class CircleComponent : Component
{
public:
	CircleComponent(class Actor* owner);

	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const { return  mRadius; };

	const Vector3& GetCenter() const { return mOwner->GetPosition(); };
private:
	float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);