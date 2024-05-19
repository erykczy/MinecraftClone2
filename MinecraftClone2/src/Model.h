#pragma once
#include "Mesh.h"
#include "Material.h"

class Model final {
public:
	Model();
	~Model();

	void render();

	void setMesh(const Mesh& mesh);
	const Mesh& getMesh() { return m_mesh; }

	void setMaterial(Material* material) { m_material = material; }
	Material* getMaterial() { return m_material; }

private:
	Mesh m_mesh{};
	Material* m_material{};
	unsigned int m_vao{};
	unsigned int m_vbo{};
	unsigned int m_ebo{};

};