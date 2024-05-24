#pragma once

#include <glm/mat4x4.hpp>

class IRenderable {
public:
	virtual ~IRenderable() = default;

	virtual void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
};