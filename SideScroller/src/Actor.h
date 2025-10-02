#pragma once

#include <vector>
#include "Math.h"

class Game;
class Component;
class Vector2;

class Actor
{
public:

	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(Game* game);

	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	State GetState() const { return mState; }
	float GetScale() const { return mScale; }
	Vector2 GetPosition() const { return mPosition; }
	float GetRotation() const { return mRotation; }
	Game* GetGame() const { return mGame; }

private:

	State mState;

	Vector2 mPosition;

	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	Game* mGame;
};