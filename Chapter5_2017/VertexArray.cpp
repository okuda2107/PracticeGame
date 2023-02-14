#include "VertexArray.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices) : mNumVerts(numVerts), mNumIndices(numIndices)
{
	//���_�z��I�u�W�F�N�g�̍쐬
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	//���_�o�b�t�@�̍쐬
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

	//���_�o�b�t�@�ɒ��_�f�[�^��R�s�[
	glBufferData
	(
		GL_ARRAY_BUFFER,
		numVerts * 3 * sizeof(float),
		verts,
		GL_STATIC_DRAW
	);

		//�C���f�b�N�X�o�b�t�@��쐬
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

	//�C���f�b�N�X�o�b�t�@�ɃC���f�b�N�X�f�[�^��R�s�[
	glBufferData
	(
		GL_ELEMENT_ARRAY_BUFFER,
		numIndices * sizeof(unsigned int),
		indices,
		GL_STATIC_DRAW
	);

	//���_���C�A�E�g�̎w�� (���_����=���_�̎g����)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer
	(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 3,
		0
	);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteBuffers(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}

/*
*同じ頂点配列オブジェクトに頂点属性を複数指定可能 
頂点属性は属性インデックスで管理されている
頂点バッファを複数作りそれぞれ違う頂点属性を指定することが可能でその場合，同じ頂点に同じ属性を付与させたいなら配列のindexを対応させる．インデックスバッファはその頂点の並びをもとにどの三角形を用いるか定めている
*/