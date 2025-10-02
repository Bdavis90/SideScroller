#include "SpriteComponent.h"
#include "SDL_image.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner), mTexture(nullptr), mTexHeight(0), mTexWidth(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_FRect r;

		// Scale the width/height by the owner's scale
		r.w = mTexWidth * mOwner->GetScale();
		r.h = mTexHeight * mOwner->GetScale();

		// Center the rectangle around the position of the owner
		r.x = mOwner->GetPosition().x - r.w / 2;
		r.x = mOwner->GetPosition().y - r.h / 2;

		SDL_RenderTextureRotated(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;

	SDL_GetTextureSize(mTexture, &mTexWidth, &mTexHeight);

}
