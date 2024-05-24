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
	class Submodel final {
	public:
		std::vector<float> vertices{};
		std::vector<unsigned int> indicies{};
		unsigned int m_vao{};
		unsigned int m_vbo{};
		unsigned int m_ebo{};

		Submodel();

		void render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
		void updateVao();

		int getSizeOfVertices() {
			static_assert(typeid(vertices) == typeid(std::vector<float>));
			return static_cast<int>(sizeof(float) * vertices.size());
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

		int chunkX{ m_chunk.getPosition().x };
		int chunkZ{ m_chunk.getPosition().y };

		for (int x{ 0 }; x < CHUNK_WIDTH; ++x) {
			for (int z{ 0 }; z < CHUNK_WIDTH; ++z) {
				for (int y{ 0 }; y < CHUNK_HEIGHT; ++y) {
					addBlock(m_submodels[m_chunk.m_blocks[x][y][z]], chunkX + x, y, chunkZ + z);
				}
			}
		}

		for (int i{ 0 }; i < m_submodels.size(); ++i) {
			m_submodels[i].updateVao();
		}
	}

	void addBlock(Submodel& submodel, int worldX, int worldY, int worldZ) {
		short blockState{ m_chunk.m_blocks[worldX][worldY][worldZ] };
		auto& vertices{ submodel.vertices };
		auto& indicies{ submodel.indicies };

		constexpr float m{ 0.5f };
		addPlane(
			submodel,
			worldX - m, worldY - m, worldZ - m,
			worldX + m, worldY - m, worldZ - m,
			worldX + m, worldY + m, worldZ - m,
			worldX - m, worldY + m, worldZ - m
			); // front
		addPlane(
			submodel,
			worldX + m, worldY - m, worldZ + m,
			worldX - m, worldY - m, worldZ + m,
			worldX - m, worldY + m, worldZ + m,
			worldX + m, worldY + m, worldZ + m
		); // back
		addPlane(
			submodel,
			worldX - m, worldY - m, worldZ + m,
			worldX + m, worldY - m, worldZ + m,
			worldX + m, worldY - m, worldZ - m,
			worldX - m, worldY - m, worldZ - m
		); // down
		addPlane(
			submodel,
			worldX -m, worldY + m, worldZ - m,
			worldX +m, worldY + m, worldZ - m,
			worldX +m, worldY + m, worldZ + m,
			worldX -m, worldY + m, worldZ + m
		); // up
		addPlane(
			submodel,
			worldX + m, worldY - m, worldZ - m,
			worldX + m, worldY - m, worldZ + m,
			worldX + m, worldY + m, worldZ + m,
			worldX + m, worldY + m, worldZ - m
		); // right
		addPlane(
			submodel,
			worldX - m, worldY - m, worldZ + m,
			worldX - m, worldY - m, worldZ - m,
			worldX - m, worldY + m, worldZ - m,
			worldX - m, worldY + m, worldZ + m
		); // left
	}

	void addPlane(
		Submodel& submodel,
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float x4, float y4, float z4
	) {
		unsigned int startIndex{ static_cast<unsigned int>(submodel.vertices.size() / 3) };

		// vertices
		submodel.vertices.push_back(x1);
		submodel.vertices.push_back(y1);
		submodel.vertices.push_back(z1);

		submodel.vertices.push_back(x2);
		submodel.vertices.push_back(y2);
		submodel.vertices.push_back(z2);

		submodel.vertices.push_back(x3);
		submodel.vertices.push_back(y3);
		submodel.vertices.push_back(z3);

		submodel.vertices.push_back(x4);
		submodel.vertices.push_back(y4);
		submodel.vertices.push_back(z4);

		// indicies
		submodel.indicies.push_back(startIndex + 0);
		submodel.indicies.push_back(startIndex + 1);
		submodel.indicies.push_back(startIndex + 2);

		submodel.indicies.push_back(startIndex + 0);
		submodel.indicies.push_back(startIndex + 2);
		submodel.indicies.push_back(startIndex + 3);
	}

};
