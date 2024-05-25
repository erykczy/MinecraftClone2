#pragma once
#include "src/rendering/IRenderable.h"
#include "src/world/Chunk.h"
#include "src/event/IChunkEventListener.h"
#include "src/rendering/Material.h"
#include <vector>

class ChunkModel final : public IRenderable, private IChunkEventListener {
public:
	ChunkModel(Chunk& chunk, Material& material) : m_chunk{ chunk }, m_material{ material } {
		m_chunk.addListener(this);
		generateSubmodels();
	}

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

		int getSizeOfVertices() {
			static_assert(typeid(vertices) == typeid(std::vector<Vertex>));
			return static_cast<int>(sizeof(Vertex) * vertices.size());
		}

		int getSizeOfIndicies() {
			static_assert(typeid(indicies) == typeid(std::vector<unsigned int>));
			return static_cast<int>(sizeof(int) * indicies.size());
		}
	};

	Material& m_material;
	Chunk& m_chunk;
	std::vector<Submodel> m_submodels{};

	void onBlockChanged(const glm::ivec3& pos) override {
		generateSubmodels();
	}

	void generateSubmodels() {
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
					addBlock(m_submodels[m_chunk.m_blocks[x][y][z]], chunkX + x, y, chunkZ + z);
				}
			}
		}

		for (auto& submodel : m_submodels) {
			submodel.updateVao();
		}
	}

	void addBlock(Submodel& submodel, int worldX, int worldY, int worldZ) {
		short blockState{ m_chunk.m_blocks[worldX][worldY][worldZ] };

		constexpr float m{ 0.5f };
		addPlane(
			submodel,
			worldX - m, worldY - m, worldZ - m,
			worldX + m, worldY - m, worldZ - m,
			worldX + m, worldY + m, worldZ - m,
			worldX - m, worldY + m, worldZ - m,
			0.0f, 0.0f, -1.0f
			); // front
		addPlane(
			submodel,
			worldX + m, worldY - m, worldZ + m,
			worldX - m, worldY - m, worldZ + m,
			worldX - m, worldY + m, worldZ + m,
			worldX + m, worldY + m, worldZ + m,
			0.0f, 0.0f, 1.0f
		); // back
		addPlane(
			submodel,
			worldX - m, worldY - m, worldZ + m,
			worldX + m, worldY - m, worldZ + m,
			worldX + m, worldY - m, worldZ - m,
			worldX - m, worldY - m, worldZ - m,
			0.0f, -1.0f, 0.0f
		); // down
		addPlane(
			submodel,
			worldX -m, worldY + m, worldZ - m,
			worldX +m, worldY + m, worldZ - m,
			worldX +m, worldY + m, worldZ + m,
			worldX -m, worldY + m, worldZ + m,
			0.0f, 1.0f, 0.0f
		); // up
		addPlane(
			submodel,
			worldX + m, worldY - m, worldZ - m,
			worldX + m, worldY - m, worldZ + m,
			worldX + m, worldY + m, worldZ + m,
			worldX + m, worldY + m, worldZ - m,
			1.0f, 0.0f, 0.0f
		); // right
		addPlane(
			submodel,
			worldX - m, worldY - m, worldZ + m,
			worldX - m, worldY - m, worldZ - m,
			worldX - m, worldY + m, worldZ - m,
			worldX - m, worldY + m, worldZ + m,
			-1.0f, 0.0f, 0.0f
		); // left
	}

	void addPlane(
		Submodel& submodel,
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float x4, float y4, float z4,
		float normalX, float normalY, float normalZ
	) {
		unsigned int startIndex{ static_cast<unsigned int>(submodel.vertices.size()) };

		// vertices
		submodel.vertices.emplace_back(x1, y1, z1, 0.0f, 0.0f, normalX, normalY, normalZ);
		submodel.vertices.emplace_back(x2, y2, z2, 1.0f, 0.0f, normalX, normalY, normalZ);
		submodel.vertices.emplace_back(x3, y3, z3, 1.0f, 1.0f, normalX, normalY, normalZ);
		submodel.vertices.emplace_back(x4, y4, z4, 0.0f, 1.0f, normalX, normalY, normalZ);

		// indicies
		submodel.indicies.push_back(startIndex + 0);
		submodel.indicies.push_back(startIndex + 1);
		submodel.indicies.push_back(startIndex + 2);

		submodel.indicies.push_back(startIndex + 0);
		submodel.indicies.push_back(startIndex + 2);
		submodel.indicies.push_back(startIndex + 3);
	}

};
