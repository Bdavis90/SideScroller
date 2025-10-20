#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game) : Actor(game), mRightSpeed(0), mDownSpeed(0)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("src/Assets/ship01.png"),
		game->GetTexture("src/Assets/ship02.png"),
		game->GetTexture("src/Assets/ship03.png"),
		game->GetTexture("src/Assets/ship04.png"),
	};

	asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();

	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.f;
	mDownSpeed = 0.f;

	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.f;
	}
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mDownSpeed -= 250.f;
	}
	if (state[SDL_SCANCODE_D])
	{
		mDownSpeed += 250.f;
	}
}
