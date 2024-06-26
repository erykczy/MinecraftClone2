#include "ClientCamera.h"
#include "src/app/util/Debug.h"
#include "src/rendering/IRenderable.h"
#include <glm/ext/matrix_transform.hpp>

ClientCamera::ClientCamera() {
	updateProjectionMatrix();
}

void ClientCamera::render(IRenderable& renderable) const {
	renderable.render(createViewMatrix(), getProjectionMatrix());
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
