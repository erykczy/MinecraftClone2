#pragma once
#include "src/rendering/IRenderable.h"
#include "src/world/Chunk.h"
#include "src/event/IChunkEventListener.h"
#include <vector>

class Material;

class ChunkModel final : public IRenderable, private IChunkEventListener {
public:
	ChunkModel(Chunk& chunk, Material& material);

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
	struct Vertex {
		float x{};
		float y{};
		float z{};
		float u{};
		float v{};
		float normalX{};
		float normalY{};
		float normalZ{};
		float ambientOcclusion{};
	};

	class Submodel final {
	public:
		std::vector<Vertex> vertices{};
		std::vector<unsigned int> indicies{};
		unsigned int m_vao{};
		unsigned int m_vbo{};
		unsigned int m_ebo{};

		Submodel();

		void render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
		void updateVao();
		void clear();

		static_assert(typeid(vertices) == typeid(std::vector<Vertex>));
		int getSizeOfVertices() { return static_cast<int>(sizeof(Vertex) * vertices.size()); }

		static_assert(typeid(indicies) == typeid(std::vector<unsigned int>));
		int getSizeOfIndicies() { return static_cast<int>(sizeof(int) * indicies.size()); }
	};

	Material& m_material;
	Chunk& m_chunk;
	std::vector<Submodel> m_submodels{};

	void onBlockChanged(const glm::ivec3& pos) override { generateSubmodels(); }

	void generateSubmodels();

	void addBlock(Submodel& submodel, const glm::ivec3& worldPos);

	void addPlane(
		Submodel& submodel,
		const glm::ivec3& worldPos,
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float x4, float y4, float z4,
		float normalX, float normalY, float normalZ
	);

	float calculateAmbientOcclusion(const glm::ivec3& worldPos, float normalX, float normalY, float normalZ, Vertex& vertex, Vertex& leftVertex, Vertex& rightVertex);

};
