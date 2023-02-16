#include "VertexArray.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices) : mNumVerts(numVerts), mNumIndices(numIndices)
{
	//頂点配列オブジェクトを作成
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	//頂点バッファを作成
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

	//頂点バッファにデータを送る
	glBufferData
	(
		GL_ARRAY_BUFFER,
		numVerts * 5 * sizeof(float),
		verts,
		GL_STATIC_DRAW
	);

		//インデックスバッファを作成
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

	//インデックスバッファにデータを送る
	glBufferData
	(
		GL_ELEMENT_ARRAY_BUFFER,
		numIndices * sizeof(unsigned int),
		indices,
		GL_STATIC_DRAW
	);

	//頂点属性を指定
	glEnableVertexAttribArray(0);
	glVertexAttribPointer
	(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 5,
		0
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 5,
		reinterpret_cast<void*>(sizeof(float) * 3)
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