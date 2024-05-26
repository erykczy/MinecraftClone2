#include "ChunkModel.h"
#include "src/world/Blocks.h"
#include <glad/glad.h>

void ChunkModel::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	for(int i = 0; i < 6; ++i)
		m_material.setTextureUnit(static_cast<std::string>("Texture[") + std::to_string(i) + ']', i);

	for (int i = 0; i < m_submodels.size(); ++i) {
		auto* blockState{ m_chunk.m_palette[i] };
		auto blockId{ blockState->blockId };
		auto* blockDef{ Blocks::all[blockId] };

		if (blockDef->getRenderingType() == BlockDef::RenderingType::NONE) continue;
		for (int j = 0; j < 6; ++j)
			blockDef->getTexture(j)->bindToTextureUnit(j);

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

void ChunkModel::Submodel::render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	material.setTransformMatricies(glm::mat4{ 1.0f }, viewMatrix, projectionMatrix);
	material.use();
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
}

void ChunkModel::Submodel::updateVao() {
	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, getSizeOfVertices(), vertices.data(), GL_DYNAMIC_DRAW);

	// indicies
	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ARRAY_BUFFER, getSizeOfIndicies(), indicies.data(), GL_DYNAMIC_DRAW);

}

void ChunkModel::Submodel::clear() {
	vertices.clear();
	indicies.clear();
}