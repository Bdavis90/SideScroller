#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game) : mState(EActive), mScale(1.f), mRotation(0.f), mGame(game)
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

void Actor::Update(float deltaTime)
{
}

void Actor::UpdateComponents(float deltaTime)
{
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
}

void Actor::RemoveComponent(Component* component)
{
}
