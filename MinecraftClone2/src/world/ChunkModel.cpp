#include "ChunkModel.h"
#include <glad/glad.h>

void ChunkModel::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	for (int i = 0; i < m_submodels.size(); ++i) {
		if (m_chunk.m_palette[i]->blockId == 0) continue; // TODO
		m_submodels[i].render(m_material, viewMatrix, projectionMatrix);
	}
}

ChunkModel::Submodel::Submodel() {
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	// indicies
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	// vertex position
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void ChunkModel::Submodel::render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	material.setTransformMatricies(glm::mat4{ 1.0f }, viewMatrix, projectionMatrix);
	material.use();
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
}

void ChunkModel::Submodel::updateVao() {
	// vertex position
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, getSizeOfVertices(), vertices.data(), GL_DYNAMIC_DRAW);

	// indicies
	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ARRAY_BUFFER, getSizeOfIndicies(), indicies.data(), GL_DYNAMIC_DRAW);
}