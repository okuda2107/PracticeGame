#include "CircleComponent.h"

CircleComponent::CircleComponent(class Actor* owner) : Component(owner)
{}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSquared();

	float radiiSq = a.GetRadius() - b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
