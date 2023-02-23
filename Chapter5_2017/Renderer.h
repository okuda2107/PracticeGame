#pragma once
#include <unordered_map>
#include <vector>
#include "SDL.h"
#include "Math.h"

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();
	//レンダラーの初期化処理と終了処理
	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	//全てのテクスチャ・メッシュを解放
	void UnloadData();
	//フレームの描画
	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);
private:
	bool LoadShaders();
	void CreateSpriteVerts();

	class Game* mGame;

	std::unordered_map<std::string, Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class MeshComponent*> mMeshComps;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;

	class Shader* mMeshShader;

	Matrix4 mView;
	Matrix4 mProjection;

	float mScreenWidth;
	float mScreenHeight;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
};
