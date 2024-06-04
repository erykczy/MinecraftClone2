#pragma once
#include <glm/vec3.hpp>

class Chunk;

class IChunkEventListener {
public:
	virtual ~IChunkEventListener() = default;

	virtual void onBlockChanged(Chunk& chunk, const glm::ivec3& blockPos) {}
};