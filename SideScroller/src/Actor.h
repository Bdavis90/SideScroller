#pragma once

#include <vector>

struct Vector2
{
	int x;
	int y;
};

class Game;
class Component;

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

private:

	State mState;

	Vector2 mPosition;

	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	Game* mGame;
};