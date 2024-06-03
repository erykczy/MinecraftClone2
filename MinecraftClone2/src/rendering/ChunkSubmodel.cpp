#include "ChunkSubmodel.h"
#include "src/rendering/Material.h"
#include <glad/glad.h>

ChunkSubmodel::ChunkSubmodel() {
	vertices = new Vertex[65536 * 8];
	indicies = new unsigned int[65536 * 6 * 2];

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
	delete[] vertices;
	delete[] indicies;
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
	glBufferData(GL_ARRAY_BUFFER, getSizeOfVertices(), vertices, GL_DYNAMIC_DRAW);

	// indicies
	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ARRAY_BUFFER, getSizeOfIndicies(), indicies, GL_DYNAMIC_DRAW);
}

void ChunkSubmodel::clear() {
	m_nextVertexIndex = 0;
	m_nextIndexIndex = 0;
}

Vertex& ChunkSubmodel::addVertex(const Vertex& vertex) {
	return vertices[m_nextVertexIndex++] = vertex;
}

unsigned int ChunkSubmodel::addIndex(unsigned int index) {
	return indicies[m_nextIndexIndex++] = index;
}
