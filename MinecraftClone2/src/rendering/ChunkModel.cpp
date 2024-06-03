#include "ChunkModel.h"
#include "src/world/def/Blocks.h"
#include "src/rendering/Material.h"
#include "src/world/Chunk.h"
#include "src/world/def/BlockDef.h"
#include "src/rendering/Texture2D.h"
#include <glad/glad.h>

ChunkModel::ChunkModel(Chunk& chunk, Material& material) : m_chunk{ chunk }, m_material{ material } {
	m_chunk.addListener(this);

	// setup material
	for (int i = 0; i < 6; ++i)
		m_material.setTextureUnit(static_cast<std::string>("Texture[") + std::to_string(i) + ']', i);

	generateSubmodels();
}

void ChunkModel::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
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

void ChunkModel::generateSubmodels() {
	if (m_submodels.size() != m_chunk.m_palette.size()) {
		m_submodels.resize(m_chunk.m_palette.size());
	}

	for (auto& submodel : m_submodels) {
		submodel.clear();
	}

	int chunkX{ m_chunk.getPosition().x };
	int chunkZ{ m_chunk.getPosition().y };

	for (int x{ 0 }; x < CHUNK_WIDTH; ++x) {
		for (int z{ 0 }; z < CHUNK_WIDTH; ++z) {
			for (int y{ 0 }; y < CHUNK_HEIGHT; ++y) {
				if (m_chunk.m_palette[m_chunk.m_blocks[x][y][z]]->getBlockDef()->getRenderingType() == BlockDef::RenderingType::NONE)
					continue;
				addBlock(m_submodels[m_chunk.m_blocks[x][y][z]], glm::ivec3{ chunkX + x, y, chunkZ + z });
			}
		}
	}

	for (auto& submodel : m_submodels) {
		submodel.updateVao();
	}
}

void ChunkModel::addBlock(ChunkSubmodel& submodel, const glm::ivec3& worldPos) {
	short blockState{ m_chunk.m_blocks[worldPos.x][worldPos.y][worldPos.z] };

	constexpr float m{ 0.5f };
	addPlane(
		submodel,
		worldPos,
		-m, -m, -m,
		+m, -m, -m,
		+m, +m, -m,
		-m, +m, -m,
		0.0f, 0.0f, -1.0f
	); // front
	addPlane(
		submodel,
		worldPos,
		+m, -m, +m,
		-m, -m, +m,
		-m, +m, +m,
		+m, +m, +m,
		0.0f, 0.0f, 1.0f
	); // back
	addPlane(
		submodel,
		worldPos,
		-m, -m, +m,
		+m, -m, +m,
		+m, -m, -m,
		-m, -m, -m,
		0.0f, -1.0f, 0.0f
	); // down
	addPlane(
		submodel,
		worldPos,
		-m, +m, -m,
		+m, +m, -m,
		+m, +m, +m,
		-m, +m, +m,
		0.0f, 1.0f, 0.0f
	); // up
	addPlane(
		submodel,
		worldPos,
		+m, -m, -m,
		+m, -m, +m,
		+m, +m, +m,
		+m, +m, -m,
		1.0f, 0.0f, 0.0f
	); // right
	addPlane(
		submodel,
		worldPos,
		-m, -m, +m,
		-m, -m, -m,
		-m, +m, -m,
		-m, +m, +m,
		-1.0f, 0.0f, 0.0f
	); // left
}

void ChunkModel::addPlane(
	ChunkSubmodel& submodel,
	const glm::ivec3& worldPos,
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	float x4, float y4, float z4,
	float normalX, float normalY, float normalZ
) {
	int startIndex{ submodel.getCountOfVertices() };

	// vertices
	auto& v0{ submodel.addVertex(Vertex{ worldPos.x + x1, worldPos.y + y1, worldPos.z + z1, 0.0f, 0.0f, normalX, normalY, normalZ, 0.0f}) };
	auto& v1{ submodel.addVertex(Vertex{ worldPos.x + x2, worldPos.y + y2, worldPos.z + z2, 1.0f, 0.0f, normalX, normalY, normalZ, 0.0f }) };
	auto& v2{ submodel.addVertex(Vertex{ worldPos.x + x3, worldPos.y + y3, worldPos.z + z3, 1.0f, 1.0f, normalX, normalY, normalZ, 0.0f }) };
	auto& v3{ submodel.addVertex(Vertex{ worldPos.x + x4, worldPos.y + y4, worldPos.z + z4, 0.0f, 1.0f, normalX, normalY, normalZ, 0.0f }) };

	// ambient occlusion TODO: optimize
	/*v0.ambientOcclusion = calculateAmbientOcclusion(worldPos, normalX, normalY, normalZ, v0, v1, v3);
	v1.ambientOcclusion = calculateAmbientOcclusion(worldPos, normalX, normalY, normalZ, v1, v2, v0);
	v2.ambientOcclusion = calculateAmbientOcclusion(worldPos, normalX, normalY, normalZ, v2, v3, v1);
	v3.ambientOcclusion = calculateAmbientOcclusion(worldPos, normalX, normalY, normalZ, v3, v0, v2);*/

	// indicies
	submodel.addIndex(startIndex + 0);
	submodel.addIndex(startIndex + 1);
	submodel.addIndex(startIndex + 2);

	submodel.addIndex(startIndex + 0);
	submodel.addIndex(startIndex + 2);
	submodel.addIndex(startIndex + 3);
}

float ChunkModel::calculateAmbientOcclusion(const glm::ivec3& worldPos, float normalX, float normalY, float normalZ, Vertex& vertex, Vertex& leftVertex, Vertex& rightVertex) {
	glm::vec3 x{ glm::normalize(glm::vec3{vertex.x - leftVertex.x, vertex.y - leftVertex.y, vertex.z - leftVertex.z}) };
	glm::vec3 z{ glm::normalize(glm::vec3{vertex.x - rightVertex.x, vertex.y - rightVertex.y, vertex.z - rightVertex.z}) };
	glm::vec3 y{ normalX, normalY, normalZ };
	auto* leftSide{ m_chunk.getBlock(glm::vec3{worldPos} + y + z) };
	auto* rightSide{ m_chunk.getBlock(glm::vec3{worldPos} + y + x) };
	auto* corner{ m_chunk.getBlock(glm::vec3{worldPos} + y + x + z) };
	bool isLeftSide{ leftSide && leftSide->blockId != 0 };
	bool isRightSide{ rightSide && rightSide->blockId != 0 };
	bool isCorner{ corner && corner->blockId != 0 };

	if (isLeftSide && isRightSide)
		return 1.0f;
	return (isLeftSide + isRightSide + isCorner) / 3.0f;
}