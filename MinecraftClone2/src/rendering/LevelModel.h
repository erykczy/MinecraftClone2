#pragma once
#include "src/rendering/IRenderable.h"
#include "src/rendering/ChunkModel.h"
#include "src/world/Level.h"

class LevelModel final : public IRenderable, private ILevelEventListener, private IChunkEventListener {
public:
	LevelModel(Level& level, Material& material);

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
	Material& m_material;
	Level& m_level;
	std::unordered_map<glm::ivec2, ChunkModel, IVec2Hash> m_chunkModels{};

	void onChunkAdded(Level& level, Chunk& chunk) override;
	void onBlockChanged(Chunk& chunk, const glm::ivec3& blockPos) override;

	void updateChunkModels(Chunk& center);
};