#pragma once
#include "src/rendering/IRenderable.h"
#include "src/world/Chunk.h"
#include "src/event/IChunkEventListener.h"
#include "src/rendering/Material.h"
#include "src/rendering/Mesh.h"
#include "src/rendering/Model.h"
#include <vector>

class ChunkModel final : public IRenderable, private IChunkEventListener {
public:
	ChunkModel(Chunk& chunk, Material& material) : m_chunk{ chunk }, m_material{ material } {
		m_chunk.addListener(this);
		generateSubmodels();
	}

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
	Material& m_material;
	Chunk& m_chunk;
	std::vector<Model> m_submodels{};

	void onBlockChanged(const glm::ivec3& pos) override {
		generateSubmodels();
	}

	void generateSubmodels() {
		if (m_submodels.size() != m_chunk.m_palette.size()) {
			m_submodels.resize(m_chunk.m_palette.size());
		}

		std::vector<Mesh> submeshes(m_submodels.size());

		int chunkX{ m_chunk.getPosition().x };
		int chunkZ{ m_chunk.getPosition().y };

		for (int x{ 0 }; x < CHUNK_WIDTH; ++x) {
			for (int z{ 0 }; z < CHUNK_WIDTH; ++z) {
				for (int y{ 0 }; y < CHUNK_HEIGHT; ++y) {
					addBlock(submeshes, chunkX + x, y, chunkZ + z);
				}
			}
		}

		for (int i{ 0 }; i < m_submodels.size(); ++i) {
			m_submodels[i].setMesh(submeshes[i]);
		}
	}

	void addBlock(std::vector<Mesh>& meshes, int worldX, int worldY, int worldZ) {
		short blockState{ m_chunk.m_blocks[worldX][worldY][worldZ] };
		std::vector<float>& vertices{ meshes[blockState].vertices };
		std::vector<unsigned int>& indicies{ meshes[blockState].indicies };

		constexpr float m{ 0.5f };
		addPlane(
			vertices, indicies,
			worldX - m, worldY -m, worldZ -m,
			worldX +m, worldY -m, worldZ -m,
			worldX +m, worldY +m, worldZ -m,
			worldX -m, worldY +m, worldZ -m
			); // front
		addPlane(
			vertices, indicies,
			+m, -m, +m,
			-m, -m, +m,
			-m, +m, +m,
			+m, +m, +m
			); // back
		addPlane(
			vertices, indicies,
			-m, -m, +m,
			+m, -m, +m,
			+m, -m, -m,
			-m, -m, -m
		); // down
		addPlane(
			vertices, indicies,
			-m, +m, -m,
			+m, +m, -m,
			+m, +m, +m,
			-m, +m, +m
		); // up
		addPlane(
			vertices, indicies,
			+m, -m, -m,
			+m, -m, +m,
			+m, +m, +m,
			+m, +m, -m
		); // right
		addPlane(
			vertices, indicies,
			-m, -m, +m,
			-m, -m, -m,
			-m, +m, -m,
			-m, +m, +m
		); // left
	}

	void addPlane(
		std::vector<float>& vertices,
		std::vector<unsigned int>& indicies,
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float x4, float y4, float z4
	) {
		unsigned int startIndex{ static_cast<unsigned int>(vertices.size() / 3) };

		// vertices
		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(z1);

		vertices.push_back(x2);
		vertices.push_back(y2);
		vertices.push_back(z2);

		vertices.push_back(x3);
		vertices.push_back(y3);
		vertices.push_back(z3);

		vertices.push_back(x4);
		vertices.push_back(y4);
		vertices.push_back(z4);

		// indicies
		indicies.push_back(startIndex + 0);
		indicies.push_back(startIndex + 1);
		indicies.push_back(startIndex + 2);

		indicies.push_back(startIndex + 0);
		indicies.push_back(startIndex + 2);
		indicies.push_back(startIndex + 3);
	}

};