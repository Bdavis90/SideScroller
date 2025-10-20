#include <algorithm>
#include <SDL_image.h>
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Math.h"

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false)
{
}

bool Game::Initialize()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("There was an error with initialization: %s", SDL_GetError());
		return false;
	}

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

	LoadData();

	return true;

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
	UnloadData();
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

void Game::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto it = mSprites.begin();
	for (it; it != mSprites.end(); ++it)
	{
		if (myDrawOrder < (*it)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(it, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto it = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(it);
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

	mShip->ProcessKeyboard((uint8_t*)state);

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
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	for (auto& sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}


	SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;

	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{

		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_DestroySurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to covert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}

	return tex;
}

void Game::LoadData()
{
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(100.f, 384.f));
	mShip->SetScale(1.5f);

	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));

	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.f, 768.f));

	std::vector<SDL_Texture*> bgTexs = {
		GetTexture("src/Assets/Farback01.png"),
		GetTexture("src/Assets/Farback01.png")
	};

	bg->SetBGTextures(bgTexs);
	bg->SetScrollSpeed(-200.f);

	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.f, 768.f));
	bgTexs = {
		GetTexture("src/Assets/Stars.png"),
		GetTexture("src/Assets/Stars.png")
	};
	bg->SetBGTextures(bgTexs);
	bg->SetScrollSpeed(-200.f);
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}

	mTextures.clear();
}
