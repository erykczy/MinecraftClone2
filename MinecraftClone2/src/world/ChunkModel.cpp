#include "ChunkModel.h"
#include "src/world/Blocks.h"
#include <glad/glad.h>

void ChunkModel::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	m_material.setTextureUnit("FrontTexture", 0);

	for (int i = 0; i < m_submodels.size(); ++i) {
		auto* blockState{ m_chunk.m_palette[i] };
		auto blockId{ blockState->blockId };

		auto* texture{ Blocks::all[blockId]->getTexture(Side::FRONT) }; // TODO more sideeess
		if (!texture) continue;
		texture->bindToTextureUnit(0);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void ChunkModel::Submodel::render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	/*static int a = 0;
	a++;
	if (a == 1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		Debug::logger << "GetBuffer:start!" << Debug::endDebug;
		int vertSize = vertices.size();
		int texSize = texCoords.size();
		float* data = new float[vertSize + texSize];
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, getSizeOfVertices() + getSizeOfTexCoords(), data);
		std::vector<float> vectorData{};
		for (int i = 0; i < vertSize + texSize; i++)
			vectorData.push_back(data[i]);

		Debug::logger << "GetBuffer:end!" << Debug::endDebug;
	}*/

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