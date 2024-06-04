#include "LevelModel.h"

LevelModel::LevelModel(Level& level, Material& material) : m_material{ material }, m_level{ level } {
	level.addListener(this);
}

void LevelModel::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	for (auto& pair : m_chunkModels) {
		pair.second.render(viewMatrix, projectionMatrix);
	}
}

void LevelModel::onChunkAdded(Level& level, Chunk& chunk)
{
	m_chunkModels.try_emplace(chunk.getPosition(), &chunk, &m_material);
	updateChunkModels(chunk);
}

void LevelModel::onBlockChanged(Chunk& chunk, const glm::ivec3& blockPos)
{
	updateChunkModels(chunk);
}

void LevelModel::updateChunkModels(Chunk& center)
{
	auto centerPos{ center.getPosition() };
	auto westPos{ centerPos + glm::ivec2{ -1, 0 } };
	auto eastPos{ centerPos + glm::ivec2{ 1, 0 } };
	auto northPos{ centerPos + glm::ivec2{ 0, 1 } };
	auto southPos{ centerPos + glm::ivec2{ 0, -1 } };

	auto* west{ m_level.getChunk(westPos, false) };
	auto* east{ m_level.getChunk(eastPos, false) };
	auto* north{ m_level.getChunk(northPos, false) };
	auto* south{ m_level.getChunk(southPos, false) };

	if (west) m_chunkModels[westPos].update();
	if (east) m_chunkModels[eastPos].update();
	if (north) m_chunkModels[northPos].update();
	if (south) m_chunkModels[southPos].update();
	m_chunkModels[centerPos].update();
}
