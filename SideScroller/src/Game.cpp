#include "Game.h"
#include <algorithm>
#include "Actor.h"

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false)
{
}

bool Game::Initialize()
{
    return false;
}

void Game::RunLoop()
{
}

void Game::Shutdown()
{
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
}
