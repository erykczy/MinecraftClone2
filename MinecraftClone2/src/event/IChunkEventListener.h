#pragma once
#include <glm/vec3.hpp>

class Chunk;

class IChunkEventListener {
public:
	virtual ~IChunkEventListener() = default;

	virtual void onBlockChanged(const glm::ivec3& pos) {}
};