#include "CircleComponent.h"

CircleComponent::CircleComponent(class Actor* owner) : Component(owner)
{}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	Vector3 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	float radiiSq = a.GetRadius() - b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
