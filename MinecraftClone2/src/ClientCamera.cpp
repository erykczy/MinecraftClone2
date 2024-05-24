#include "src/ClientCamera.h"
#include "src/Debug.h"
#include "src/Model.h"
#include <glm/ext/matrix_transform.hpp>

ClientCamera::ClientCamera() {
	updateProjectionMatrix();
}

void ClientCamera::renderModel(const Model& model) const {
	model.render(createViewMatrix(), getProjectionMatrix());
}

glm::mat4 ClientCamera::createViewMatrix() const
{
	return glm::lookAtLH(position, position + getForward(), getUp());
}

void ClientCamera::setFov(float valueDegrees) {
	m_fovDegrees = valueDegrees;
	updateProjectionMatrix();
}

void ClientCamera::setNearPlane(float value) {
	m_nearPlane = value;
	updateProjectionMatrix();
}

void ClientCamera::setFarPlane(float value) {
	m_farPlane = value;
	updateProjectionMatrix();
}

void ClientCamera::setAspectRatio(float value) {
	m_aspectRatio = value;
	updateProjectionMatrix();
}
