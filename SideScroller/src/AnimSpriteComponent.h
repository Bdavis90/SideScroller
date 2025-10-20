#pragma once
#include "SpriteComponent.h"
#include <vector>

class Actor;

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* owner, int drawOrder = 100);

	void Update(float deltaTime);
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float animFPS) { mAnimFPS = animFPS; }

private:

	std::vector<SDL_Texture*> mAnimTextures;

	float mCurrFrame;

	float mAnimFPS;
};