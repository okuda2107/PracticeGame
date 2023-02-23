#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder) : Component(owner), mDrawOrder(drawOrder), mTexHeight(128), mTexWidth(128), mTexture(nullptr)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(mTexWidth),
		static_cast<float>(mTexHeight),
		1.0f);
	Matrix4 world = scaleMat * mOwner->GetWorldTransform();

	shader->SetMatrixUniform("uWorldTransform", world);
	
	mTexture->SetActive();

	glDrawElements(
		GL_TRIANGLES,
		6,
		GL_UNSIGNED_INT,
		nullptr
	);
}

void SpriteComponent::SetTexture(Texture* tex)
{
	mTexture = tex;
	mTexWidth = tex->GetWidth();
	mTexHeight = tex->GetHeight();
}