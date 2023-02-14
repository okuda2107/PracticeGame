#include "Shader.h"
#include <fstream>
#include <sstream>
#include "SDL.h"

Shader::Shader() : mShaderProgram(0), mVertexShader(0), mFragShader(0)
{}

Shader::~Shader()
{}

bool Shader::CompileShader(const std::string& filename, GLuint shaderType, GLuint& outShader)
{
	//�t�@�C����J��
	std::ifstream shaderFile(filename);
	if (shaderFile.is_open())
	{
		//���ׂẴe�L�X�g��1�̕�����ɓǂݍ���
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		//�w�肳�ꂽ�^�C�v�̃V�F�[�_�[��쐬
		outShader = glCreateShader(shaderType);
		//�ǂݍ��񂾕�����ł̃R���p�C������݂�
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile Shader %s", filename.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Can't find Shader file %s", filename.c_str());
		return false;
	}
	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	//�R���p�C����Ԃ�₢���킹��
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("Failed to Compile of GLSL brfore produce Shader File :\n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	//���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[��R���p�C������
	if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) || !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}
	//���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[������N���ăV�F�[�_�[�v���O��������
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);
	if (!IsValidProgram())
	{
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	//�R���p�C����Ԃ�₢���킹��
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("Failed to Compile of GLSL after produce to Shader File :\n%s", buffer);
		return false;
	}
	return true;
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	// Search uniform
	GLuint loc = glGetUniformLocation(mShaderProgram, name);

	//send Matrix data to uniform
	glUniformMatrix4fv(
		loc,
		1,
		GL_TRUE,
		matrix.GetAsFloatPtr()
	);
}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}