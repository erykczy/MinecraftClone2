#pragma once
#include "src/rendering/IRenderable.h"
#include "src/rendering/ChunkSubmodel.h"
#include "src/event/IChunkEventListener.h"
#include <vector>

class Material;
class Chunk;

class ChunkModel final : public IRenderable, private IChunkEventListener {
public:
	ChunkModel(Chunk& chunk, Material& material);

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
	Material& m_material;
	Chunk& m_chunk;
	std::vector<ChunkSubmodel> m_submodels{};

	void onBlockChanged(const glm::ivec3& pos) override { generateSubmodels(); }

	void generateSubmodels();

	void addBlock(ChunkSubmodel& submodel, const glm::ivec3& worldPos);

	void addPlane(
		ChunkSubmodel& submodel,
		const glm::ivec3& worldPos,
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float x4, float y4, float z4,
		float normalX, float normalY, float normalZ
	);

	float calculateAmbientOcclusion(const glm::ivec3& worldPos, float normalX, float normalY, float normalZ, Vertex& vertex, Vertex& leftVertex, Vertex& rightVertex);

};
