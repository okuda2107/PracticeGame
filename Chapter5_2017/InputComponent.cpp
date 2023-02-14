#include "InputComponent.h"

InputComponent::InputComponent(class Actor*owner) : MoveComponent(owner)
{}

void InputComponent::ProcessInput(const uint8_t* keystate)
{
	float forwardSpeed = 0.0f;
	if (keystate[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keystate[mBackKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keystate[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keystate[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}