#pragma once
#include "Model.h"
#include "src/rendering/ClientCamera.h"
#include "src/rendering/Material.h"
#include <glad/glad.h>

Model::Model() {
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	// indicies
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	// vertex position
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

Model::~Model() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

void Model::setMesh(const Mesh& mesh)
{
	m_mesh = mesh;

	// vertex position
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_mesh.getSizeOfVertices(), m_mesh.vertices.data(), GL_DYNAMIC_DRAW);

	// indicies
	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ARRAY_BUFFER, m_mesh.getSizeOfIndicies(), m_mesh.indicies.data(), GL_DYNAMIC_DRAW);
}

void Model::render(Material& material, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	material.setTransformMatricies(m_modelMatrix, viewMatrix, projectionMatrix);
	material.use();
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_mesh.indicies.size(), GL_UNSIGNED_INT, 0);
}

void Model::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	if (!m_material) {
		Debug::logger << "Material is nullptr!" << Debug::endError;
		return;
	}
	render(*m_material, viewMatrix, projectionMatrix);
}

void Model::setPosition(const glm::vec3& value) {
	m_position = value;
	updateModelMatrix();
}

void Model::updateModelMatrix() {
	m_modelMatrix = glm::translate(glm::mat4{ 1.0 }, m_position);
}
