#include "Game.h"
#include "Actor.h"
#include <vector>
#include <algorithm>
#include "SpriteComponent.h"
#include "glew.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Ship.h"
#include "Asteroid.h"

Game::Game() : mWindow(nullptr), mContext(nullptr), mIsRunning(true), mTicksCount(0), mUpdatingActors(false), mShip(nullptr), mSpriteShader(nullptr), mSpriteVerts(nullptr)
{}

bool Game::Initialize()
{
	if (int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("Failed to Initialize SDL:%s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow(
		"Game Programming in C++",
		100,
		100,
		1024,
		768,
		SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Faled to Create Window:%s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to Initialize GLEW");
		return false;
	}
	glGetError();
	
	if (!LoadShaders())
	{
		SDL_Log("Failed to Load Shaders");
		return false;
	}
	
	InitSpriteVerts();

	LoadData();

	mTicksCount = SDL_GetTicks();

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

void Game::ProcessInput()
{
	SDL_Event mEvent;
	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
			case SDL_QUIT:
				mIsRunning = false;
				break;
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltatime > 0.05f)
	{
		deltatime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	UpdateActors(deltatime);
}

void Game::GenerateOutput()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	for (auto sprites : mSprites)
	{
		sprites->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

void Game::Shutdown()
{
	UnLoadData();
	
	mSpriteShader->Unload();
	delete mSpriteShader;
	delete mSpriteVerts;

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(class Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.push_back(actor);
	}
	else
	{
		mActors.push_back(actor);
	}
}

void Game::RemoveActor(class Actor* actor)
{
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::UpdateActors(float deltatime)
{
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltatime);
	}
	mUpdatingActors = false;
	
	for (auto pending : mPendingActors)
	{
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::State::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::AddSprite(class SpriteComponent* sprite)
{
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if ((*iter)->GetDrawOrder() > sprite->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(class SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(filename.c_str()); //ここで読み込まない(解決)
		if (!surf)
		{
			SDL_Log("画像の読み込みに失敗:%s", filename.c_str());
			return nullptr;
		}
		//tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		//SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("サーフェイスからテクスチャに変換失敗:%s", filename.c_str());
			return nullptr;
		}
		mTextures.emplace(filename, tex);
	}
	return tex;
}

bool Game::LoadShaders()
{
	mSpriteShader = new  Shader();

	if (!mSpriteShader->Load("Shaders/Basic.vert", "Shaders/Basic.frag"))
	{
		return false;
	}
	mSpriteShader->SetActive();
	/*
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.0f, 768.0f);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	*/

	return true;
}

void Game::InitSpriteVerts()
{
	float vertexBuffer[] = {
		-0.5f,  0.5f, 0.f, // top left
		 0.5f,  0.5f, 0.f, // top right
		 0.5f, -0.5f, 0.f, // bottom right
		-0.5f, -0.5f, 0.f  // bottom left
	};

	unsigned int indexBuffer[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}

void Game::LoadData()
{
	const int numAsteroids = 10;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

void Game::UnLoadData()
{
	while (!mSprites.empty())
	{
		delete mSprites.back();
	}
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
	//erase()はメモリの解放はしないが、メモリの内容をnullにする
}