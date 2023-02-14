#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(class Game* game) : mGame(game), mScale(1.0f), mRotation(0.0f), mState(State::EActive), mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::ProcessInput(const uint8_t* keystate)
{
	if (mState == State::EActive)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keystate);
		}
		ActorInput(keystate);
	}
}

void Actor::Update(float deltatime)
{
	if (mState == State::EActive)
	{
		ComputeWorldTransform();
		UpdateComponent(deltatime);
		UpdateActor(deltatime);
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponent(float deltatime)
{
	for (auto component : mComponents)
	{
		component->Update(deltatime);
	}
}

void Actor::UpdateActor(float deltatime)
{}

void Actor::AddComponent(class Component* component)
{
	int updateOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (updateOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(class Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// scaling, rotation, translation
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 1.0f));
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}

	}
}