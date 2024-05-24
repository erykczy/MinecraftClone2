#include "src/ClientCamera.h"
#include "src/Debug.h"
#include <glm/ext/matrix_transform.hpp>

ClientCamera::ClientCamera() {
	updateProjectionMatrix();
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
	if (m_autoAspectRatio)
		Debug::logger << "You are trying to change aspect ratio while it is updated automatically. Change autoAspectRatio value!" << Debug::endWarning;
	m_aspectRatio = value;
	updateProjectionMatrix();
}

void ClientCamera::setAutoAspectRatio(bool value) {
	m_autoAspectRatio = value;
	// TODO
	/*if (m_autoAspectRatio) {
		m_aspectRatio = Window::s_activeWindow->getAspectRatio();
		Window::s_activeWindow->addListener(this);
	}
	else {
		Window::s_activeWindow->removeListener(this);
	}*/
}
