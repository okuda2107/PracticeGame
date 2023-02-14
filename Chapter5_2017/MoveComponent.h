#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltatime);

	void SetAngularSpeed(float angSpeed) { mAngularSpeed = angSpeed; }
	void SetForwardSpeed(float forwSpeed) { mForwardSpeed = forwSpeed; }
private:
	float mAngularSpeed;
	float mForwardSpeed;
};