#pragma once
#include <SDL3/SDL.h>
#include <vector>

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

// Game class
class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();
	void AddActor(class Actor* actor);
	void RemoveActor(Actor* actor);


private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();


	SDL_Window* mWindow;

	SDL_Renderer* mRenderer;

	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;

};