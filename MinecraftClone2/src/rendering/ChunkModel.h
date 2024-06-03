#pragma once
#include "src/rendering/IRenderable.h"
#include "src/rendering/ChunkSubmodel.h"
#include "src/event/IChunkEventListener.h"
#include <vector>

using intPosRef = const glm::ivec3&;
using posRef = const glm::vec3&;
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

	void onBlockChanged(intPosRef pos) override { generateSubmodels(); }

	void generateSubmodels();

	void addBlock(ChunkSubmodel& submodel, intPosRef worldPos);

	void addFace(
		ChunkSubmodel& submodel,
		intPosRef worldPos,
		posRef centerPos,
		intPosRef cornerRel0,
		intPosRef cornerRel1,
		intPosRef cornerRel2,
		intPosRef cornerRel3,
		float normalX, float normalY, float normalZ
	);

	float calculateAmbientOcclusion(intPosRef worldPos, intPosRef sideLeft, intPosRef sideRight, intPosRef corner);

};
