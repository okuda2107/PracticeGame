#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	~Component();

	virtual void ProcessInput(const uint8_t* keystate)
	{}

	virtual void Update(float deltatime);

	virtual void OnUpdateWorldTransform() {}

	const int GetUpdateOrder() { return mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};