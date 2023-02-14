#pragma once
#include <string>
#include "glew.h"
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	//指定された名前の頂点/フラグメントシェーダーを読み込む
	bool Load(const std::string& vertName,
		const std::string& fragName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	//シェーダーをコンパイルする
	bool CompileShader(const std::string& filename, GLenum shaderType, GLuint& outShader);
	//シェーダーのコンパイルに成功したかどうかの判定
	bool IsCompiled(GLuint shader);
	//頂点/フラグメントプログラムのリングを確認
	bool IsValidProgram();
	//シェーダーオブジェクトのIDを格納
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};