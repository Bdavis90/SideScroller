#pragma once
#include <SDL3/SDL.h>
#include <vector>


class Actor;
// Game class
class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();
	void AddActor(Actor* actor);
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