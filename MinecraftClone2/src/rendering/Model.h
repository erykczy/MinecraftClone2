#pragma once
#include "src/rendering/Mesh.h"
#include <glm/ext/matrix_transform.hpp>

class ClientCamera;
class Material;

class Model final {
public:
	Model();
	~Model();

	void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const;

	void setMesh(const Mesh& mesh);
	const Mesh& getMesh() { return m_mesh; }

	void setMaterial(Material* material) { m_material = material; }
	Material* getMaterial() { return m_material; }

	void setPosition(const glm::vec3& value);
	const glm::vec3& getPosition() { return m_position; }

private:
	Mesh m_mesh{};
	Material* m_material{};
	unsigned int m_vao{};
	unsigned int m_vbo{};
	unsigned int m_ebo{};
	glm::vec3 m_position{};
	glm::mat4 m_modelMatrix{};

	void updateModelMatrix();

};