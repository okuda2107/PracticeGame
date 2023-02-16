#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <unordered_map>
#include <string>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void LoadData();
	void UnLoadData();

	

	class Texture* GetTexture(const std::string& filename);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void UpdateActors(float deltatime);

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	bool mIsRunning;
	Uint32 mTicksCount;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	bool mUpdatingActors;

	std::unordered_map<std::string, Texture*> mTextures;
	std::vector<class SpriteComponent*> mSprites;

	class Ship* mShip;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;

	void InitSpriteVerts();
	bool LoadShaders();
};