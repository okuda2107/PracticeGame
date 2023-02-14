#pragma once
#include "Component.h"
#include "SDL.h"
#include "SDL_image.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(SDL_Texture* tex);

	const int GetDrawOrder() { return mDrawOrder; }
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexHeight;
	int mTexWidth;
};