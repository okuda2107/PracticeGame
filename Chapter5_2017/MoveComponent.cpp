#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder) : Component(owner, updateOrder), mYAngularSpeed(0.0f), mXAngularSpeed(0.0f), mZAngularSpeed(0.0f), mForwardSpeed(0.0f)
{}

void MoveComponent::Update(float deltatime)
{
	if (!Math::NearZero(mZAngularSpeed))
	{
		Quaternion rot = mOwner->GetRotation();
		float angle = mZAngularSpeed * deltatime;
		Quaternion inc(Vector3::UnitZ, angle);
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mYAngularSpeed))
	{
		Quaternion rot = mOwner->GetRotation();
		float angle = mYAngularSpeed * deltatime;
		Quaternion inc(Vector3::UnitY, angle);
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mXAngularSpeed))
	{
		Quaternion rot = mOwner->GetRotation();
		float angle = mXAngularSpeed * deltatime;
		Quaternion inc(Vector3::UnitX, angle);
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector3 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltatime;
		mOwner->SetPosition(pos);
	}
}