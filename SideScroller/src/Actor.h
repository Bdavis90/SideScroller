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
	void SetState(State state) { mState = state; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	Game* GetGame() const { return mGame; }

private:

	State mState;

	Vector2 mPosition;

	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	Game* mGame;
};