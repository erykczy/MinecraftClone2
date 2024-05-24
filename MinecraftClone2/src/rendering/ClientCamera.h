#pragma once
#include "src/app/Constants.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Model;

class ClientCamera final {
public:
	glm::vec3 position{};
	float yaw{ 90 };
	float pitch{};

	ClientCamera();

	void renderModel(const Model& model) const;

	glm::mat4 createViewMatrix() const;
	glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }

	// returns fov in degrees
	float getFov() const { return m_fovDegrees; }

	// sets fov in degrees
	void setFov(float valueDegrees);

	float getNearPlane() const { return m_nearPlane; }
	void setNearPlane(float value);

	float getFarPlane() const { return m_nearPlane; }
	void setFarPlane(float value);

	void setAspectRatio(float value);
	float getAspectRatio() const { return m_aspectRatio; }

	glm::vec3 getForward() const {
		return glm::vec3{
			glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
			glm::sin(glm::radians(pitch)),
			glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))
		};
	}
	glm::vec3 getRight() const {
		return glm::cross(getUp(), getForward());
	}
	glm::vec3 getUp() const {
		return glm::vec3{ 0.0f, 1.0f, 0.0f }; // TODO not always true
	}

private:
	glm::mat4 m_projectionMatrix{};
	float m_fovDegrees{ Constants::defaultCameraFovDegrees };
	float m_aspectRatio{ static_cast<float>(Constants::defaultWindowWidth) / Constants::defaultWindowHeight };
	float m_farPlane{ Constants::defaultCameraFarPlane };
	float m_nearPlane{ Constants::defaultCameraNearPlane };

	void updateProjectionMatrix() {
		m_projectionMatrix = glm::perspectiveLH(glm::radians(m_fovDegrees), m_aspectRatio, m_nearPlane, m_farPlane);
	}
};