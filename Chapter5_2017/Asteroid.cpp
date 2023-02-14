#include "Random.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	Vector2 randPos = Random::GetVector(Vector2::Vector2(-512.0f, -384.0f),
		Vector2(512.0f, 384.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	//sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//MoveComponent* mc = new MoveComponent(this);
	//mc->SetForwardSpeed(150.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);
}