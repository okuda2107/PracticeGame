#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include "Shader.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder) : Component(owner), mDrawOrder(drawOrder), mTexHeight(128), mTexWidth(128), mTexture(nullptr)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	/*
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(mTexWidth),
		static_cast<float>(mTexHeight),
		1.0f);
	Matrix4 world = scaleMat * mOwner->GetWorldTransform();

	shader->SetMatrixUniform("uWorldTransform", world);
	*/

	glDrawElements(
		GL_TRIANGLES,
		6,
		GL_UNSIGNED_INT,
		nullptr
	);
}

void SpriteComponent::SetTexture(SDL_Texture* tex)
{
	mTexture = tex;
	SDL_QueryTexture(tex, nullptr, nullptr, &mTexWidth, &mTexHeight);
}