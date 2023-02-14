#pragma once
#include <string>
#include "glew.h"
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	//�w�肳�ꂽ���O�̒��_/�t���O�����g�V�F�[�_�[��ǂݍ���
	bool Load(const std::string& vertName,
		const std::string& fragName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	//�V�F�[�_�[���R���p�C������
	bool CompileShader(const std::string& filename, GLenum shaderType, GLuint& outShader);
	//�V�F�[�_�[�̃R���p�C���ɐ����������ǂ����̔���
	bool IsCompiled(GLuint shader);
	//���_/�t���O�����g�v���O�����̃����O���m�F
	bool IsValidProgram();
	//�V�F�[�_�[�I�u�W�F�N�g��ID���i�[
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};