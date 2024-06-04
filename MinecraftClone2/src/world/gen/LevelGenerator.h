#pragma once
#include "src/world/Level.h"

class LevelGenerator {
public:
	virtual ~LevelGenerator() = default;

	virtual void generateChunk(Chunk& chunk) = 0;
};
