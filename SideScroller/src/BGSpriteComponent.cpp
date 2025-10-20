#include "BGSpriteComponent.h"
#include "SDL_image.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder), mScrollSpeed(0.f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		bg.mOffset.x += mScrollSpeed * deltaTime;
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : mBGTextures)
	{
		SDL_FRect r;

		r.w = mScreenSize.x;
		r.h = mScreenSize.y;

		// Center the rectangle around the position of the owner
		r.x = mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x;
		r.x = mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y;

		SDL_RenderTexture(renderer, mTexture, nullptr, &r);

	}

}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*> textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.push_back(temp);
		count++;
	}
}
