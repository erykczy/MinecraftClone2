#pragma once
#include "src/rendering/Vertex.h"
#include <glm/mat4x4.hpp>

class Material;

class ChunkSubmodel final {
public:
	Vertex* vertices{};
	unsigned int* indicies{};
	unsigned int m_vao{};
	unsigned int m_vbo{};
	unsigned int m_ebo{};

	ChunkSubmodel();
	~ChunkSubmodel();

	void render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void updateVao();
	void clear();
	Vertex& addVertex(const Vertex& vertex);
	unsigned int addIndex(unsigned int index);
	Vertex& getVertex(int index) { return vertices[index]; }

	int getSizeOfVertices() const { return static_cast<int>(sizeof(Vertex) * m_nextVertexIndex); }
	int getSizeOfIndicies() const { return static_cast<int>(sizeof(unsigned int) * m_nextIndexIndex); }
	int getCountOfIndicies() const { return m_nextIndexIndex; }
	int getCountOfVertices() const { return m_nextVertexIndex; }

private:
	int m_nextVertexIndex{};
	int m_nextIndexIndex{};
};