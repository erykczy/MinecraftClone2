#include "ChunkModel.h"
#include "src/world/def/Blocks.h"
#include "src/world/Chunk.h"
#include "src/world/Level.h"
#include "src/world/def/BlockDef.h"
#include "src/rendering/Material.h"
#include "src/rendering/Texture2D.h"
#include <glad/glad.h>

ChunkModel::ChunkModel()
{
	Debug::logger << "Created empty ChunkModel!" << Debug::endWarning;
}

ChunkModel::ChunkModel(Chunk* chunk, Material* material) : m_chunk{ chunk }, m_level{ chunk->getLevel() }, m_material{material} {
	m_chunk->addListener(this);

	// setup material
	for (int i = 0; i < 6; ++i)
		m_material->setTextureUnit(static_cast<std::string>("Texture[") + std::to_string(i) + ']', i);
}

void ChunkModel::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	for (int i = 0; i < m_submodels.size(); ++i) {
		auto* blockState{ m_chunk->m_palette[i] };
		auto blockId{ blockState->blockId };
		auto* blockDef{ Blocks::all[blockId] };

		if (blockDef->getRenderingType() == BlockDef::RenderingType::NONE) continue;
		for (int j = 0; j < 6; ++j)
			blockDef->getTexture(j)->bindToTextureUnit(j);

		m_submodels[i].render(*m_material, viewMatrix, projectionMatrix);
	}
}

void ChunkModel::update() {
	if (m_submodels.size() != m_chunk->m_palette.size()) {
		m_submodels.resize(m_chunk->m_palette.size());
	}

	for (auto& submodel : m_submodels) {
		submodel.clear();
	}

	int chunkBlockX{ m_chunk->getPosition().x * 16 };
	int chunkBlockZ{ m_chunk->getPosition().y * 16 };

	for (int x{ 0 }; x < CHUNK_WIDTH; ++x) {
		for (int z{ 0 }; z < CHUNK_WIDTH; ++z) {
			for (int y{ 0 }; y < CHUNK_HEIGHT; ++y) {
				if (m_chunk->m_palette[m_chunk->m_blocks[x][y][z]]->getBlockDef()->getRenderingType() == BlockDef::RenderingType::NONE)
					continue;
				addBlock(m_submodels[m_chunk->m_blocks[x][y][z]], glm::ivec3{ chunkBlockX + x, y, chunkBlockZ + z });
			}
		}
	}

	for (auto& submodel : m_submodels) {
		submodel.updateVao();
	}
}

void ChunkModel::addBlock(ChunkSubmodel& submodel, intPosRef worldPos) {
	posRef centerPos{ worldPos.x + 0.5f, worldPos.y + 0.5f, worldPos.z + 0.5f };

	constexpr int m{ 1 };
	if (m_level->isAir(worldPos + glm::ivec3{ 0, 0, -1 }, false))
		addFace(
			submodel,
			worldPos, centerPos,
			{ -m, -m, -m },
			{ +m, -m, -m },
			{ +m, +m, -m },
			{ -m, +m, -m },
			0.0f, 0.0f, -1.0f
		); // front
	if (m_level->isAir(worldPos + glm::ivec3{ 0, 0, 1 }, false))
		addFace(
			submodel,
			worldPos, centerPos,
			{ +m, -m, +m },
			{ -m, -m, +m },
			{ -m, +m, +m },
			{ +m, +m, +m },
			0.0f, 0.0f, 1.0f
		); // back
	if (m_level->isAir(worldPos + glm::ivec3{ 0, -1, 0 }, false))
		addFace(
			submodel,
			worldPos, centerPos,
			{ -m, -m, +m },
			{ +m, -m, +m },
			{ +m, -m, -m },
			{ -m, -m, -m },
			0.0f, -1.0f, 0.0f
		); // down
	if (m_level->isAir(worldPos + glm::ivec3{ 0, 1, 0 }, false))
		addFace(
			submodel,
			worldPos, centerPos,
			{ -m, +m, -m },
			{ +m, +m, -m },
			{ +m, +m, +m },
			{ -m, +m, +m },
			0.0f, 1.0f, 0.0f
		); // up
	if (m_level->isAir(worldPos + glm::ivec3{ 1, 0, 0 }, false))
		addFace(
			submodel,
			worldPos, centerPos,
			{ +m, -m, -m },
			{ +m, -m, +m },
			{ +m, +m, +m },
			{ +m, +m, -m },
			1.0f, 0.0f, 0.0f
		); // right
	if (m_level->isAir(worldPos + glm::ivec3{ -1, 0, 0 }, false))
		addFace(
			submodel,
			worldPos, centerPos,
			{ -m, -m, +m },
			{ -m, -m, -m },
			{ -m, +m, -m },
			{ -m, +m, +m },
			-1.0f, 0.0f, 0.0f
		); // left
}

void ChunkModel::addFace(
	ChunkSubmodel& submodel,
	intPosRef worldPos,
	posRef centerPos,
	intPosRef cornerRel0,
	intPosRef cornerRel1,
	intPosRef cornerRel2,
	intPosRef cornerRel3,
	float normalX, float normalY, float normalZ
) {
	int startIndex{ submodel.getCountOfVertices() };

	glm::ivec3 sideRel0{ (cornerRel1 - cornerRel0) / 2 + cornerRel0 };
	glm::ivec3 sideRel1{ (cornerRel2 - cornerRel1) / 2 + cornerRel1 };
	glm::ivec3 sideRel2{ (cornerRel3 - cornerRel2) / 2 + cornerRel2 };
	glm::ivec3 sideRel3{ (cornerRel0 - cornerRel3) / 2 + cornerRel3 };

	// vertices
	auto& v0{ submodel.addVertex(Vertex{ centerPos.x + cornerRel0.x / 2.0f, centerPos.y + cornerRel0.y / 2.0f, centerPos.z + cornerRel0.z / 2.0f, 0.0f, 0.0f, normalX, normalY, normalZ, calculateAmbientOcclusion(worldPos, sideRel0, sideRel3, cornerRel0) }) };
	auto& v1{ submodel.addVertex(Vertex{ centerPos.x + cornerRel1.x / 2.0f, centerPos.y + cornerRel1.y / 2.0f, centerPos.z + cornerRel1.z / 2.0f, 1.0f, 0.0f, normalX, normalY, normalZ, calculateAmbientOcclusion(worldPos, sideRel1, sideRel0, cornerRel1) }) };
	auto& v2{ submodel.addVertex(Vertex{ centerPos.x + cornerRel2.x / 2.0f, centerPos.y + cornerRel2.y / 2.0f, centerPos.z + cornerRel2.z / 2.0f, 1.0f, 1.0f, normalX, normalY, normalZ, calculateAmbientOcclusion(worldPos, sideRel2, sideRel1, cornerRel2) }) };
	auto& v3{ submodel.addVertex(Vertex{ centerPos.x + cornerRel3.x / 2.0f, centerPos.y + cornerRel3.y / 2.0f, centerPos.z + cornerRel3.z / 2.0f, 0.0f, 1.0f, normalX, normalY, normalZ, calculateAmbientOcclusion(worldPos, sideRel3, sideRel2, cornerRel3) }) };

	// indicies
	submodel.addIndex(startIndex + 0);
	submodel.addIndex(startIndex + 1);
	submodel.addIndex(startIndex + 2);

	submodel.addIndex(startIndex + 0);
	submodel.addIndex(startIndex + 2);
	submodel.addIndex(startIndex + 3);
}

float ChunkModel::calculateAmbientOcclusion(intPosRef worldPos, intPosRef sideLeftRel, intPosRef sideRightRel, intPosRef cornerRel) {
	bool isLeftSide{ !m_level->isAir(worldPos + sideLeftRel, false) };
	bool isRightSide{ !m_level->isAir(worldPos + sideRightRel, false) };
	bool isCorner{ !m_level->isAir(worldPos + cornerRel, false) };

	if (isLeftSide && isRightSide)
		return 1.0f;
	return (isLeftSide + isRightSide + isCorner) / 3.0f;
}