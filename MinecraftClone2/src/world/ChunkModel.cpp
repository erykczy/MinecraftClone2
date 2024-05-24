#include "ChunkModel.h"
#include <glad/glad.h>

void ChunkModel::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	for (int i = 1; i < m_submodels.size(); ++i) {
		m_submodels[i].render(m_material, viewMatrix, projectionMatrix);
	}
}