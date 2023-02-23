#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keystate);

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetXKey(int key) { xRotationKey = key; }
	void Setantikey(int key) { xAnti = key; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	int xRotationKey;
	int xAnti;

	int mForwardKey;
	int mBackKey;

	int mClockwiseKey;
	int mCounterClockwiseKey;
};