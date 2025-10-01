#include "Game.h"
#include <algorithm>
#include "Actor.h"

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false)
{
}

bool Game::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	mWindow = SDL_CreateWindow("SideScroller", 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("There was an error creating the window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, NULL);
	if (!mRenderer)
	{
		SDL_Log("There was an error creating the renderer: %s", SDL_GetError());
		return false;
	}


}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.push_back(actor);
		return;
	}

	mActors.push_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
		return;
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}


}

void Game::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_EVENT_QUIT:
		mIsRunning = false;
		break;
	}

	const bool* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

}

void Game::UpdateGame()
{

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	mUpdatingActors = true;

	for (const auto& actor : mActors)
	{
		actor->Update(deltaTime);
	}

	mUpdatingActors = false;

	for (const auto& actor : mPendingActors)
	{
		mActors.push_back(actor);
	}

	mPendingActors.clear();


	std::vector<Actor*> deadActors;
	for (const auto& actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.push_back(actor);
		}
	}

	for (const auto& actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 225, 123, 45, 255);
	SDL_RenderClear(mRenderer);
	SDL_RenderPresent(mRenderer);
}
