#pragma once
#include "src/rendering/Vertex.h"
#include <glm/mat4x4.hpp>
#include <vector>

class Material;

class ChunkSubmodel final {
public:
	std::vector<Vertex> vertices{};
	std::vector<unsigned int> indicies{};
	unsigned int m_vao{};
	unsigned int m_vbo{};
	unsigned int m_ebo{};

	ChunkSubmodel();
	~ChunkSubmodel();

	void render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void updateVao();
	void clear();
	void startWriting();
	void stopWriting();
	Vertex& addVertex(const Vertex& vertex);
	unsigned int addIndex(unsigned int index);
	Vertex& getVertex(int index) { return vertices[index]; }

	int getSizeOfVertices() const { return static_cast<int>(sizeof(Vertex) * getCountOfVertices()); }
	int getSizeOfIndicies() const { return static_cast<int>(sizeof(unsigned int) * getCountOfIndicies()); }
	int getCountOfIndicies() const { return indicies.size(); }
	int getCountOfVertices() const { return vertices.size(); }
};