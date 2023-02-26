#pragma once
#include <unordered_map>
#include <vector>
#include "SDL.h"
#include "Math.h"

struct DirectionalLight
{
	//光の方向
	Vector3 mDirection;
	//拡散反射光
	Vector3 mDiffuseColor;
	//鏡面反射光
	Vector3 mSpecColor;
};

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

	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; } //全体に一つしかないのでRendererに書く
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader);
	//これは本来Shader.hファイルに書くべき？ <- 3D表示するときにしか使わんからRendererファイルでいいかも このファイルに新しく光源の配列作っても良し 光の計算はシェーダーにとっては必要不可欠ではない

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

	// Lighting data
	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
};
