#include "ChunkSubmodel.h"
#include "src/rendering/Material.h"
#include "src/world/Chunk.h"
#include <glad/glad.h>

ChunkSubmodel::ChunkSubmodel() {
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	// indicies
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ambient occlusion attribute
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
}

ChunkSubmodel::~ChunkSubmodel()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

void ChunkSubmodel::render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	material.setTransformMatricies(glm::mat4{ 1.0f }, viewMatrix, projectionMatrix);
	material.use();
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, getCountOfIndicies(), GL_UNSIGNED_INT, 0);
}

void ChunkSubmodel::updateVao() {
	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, getSizeOfVertices(), vertices.data(), GL_DYNAMIC_DRAW);

	// indicies
	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ARRAY_BUFFER, getSizeOfIndicies(), indicies.data(), GL_DYNAMIC_DRAW);
}

void ChunkSubmodel::clear() {
	vertices.clear();
	indicies.clear();
}

void ChunkSubmodel::startWriting()
{
	clear();
	vertices.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_WIDTH * 6 * 4);
	indicies.reserve(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_WIDTH * 6 * 2);
}

void ChunkSubmodel::stopWriting()
{
	vertices.shrink_to_fit();
	indicies.shrink_to_fit();
	updateVao();
}

Vertex& ChunkSubmodel::addVertex(const Vertex& vertex) {
	vertices.push_back(vertex);
	return vertices.back();
}

unsigned int ChunkSubmodel::addIndex(unsigned int index) {
	indicies.push_back(index);
	return indicies.back();
}
