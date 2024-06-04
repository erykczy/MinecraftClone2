#pragma once
#include "src/world/gen/LevelGenerator.h"

class BasicLevelGenerator final : public LevelGenerator {
public:
	void generateChunk(Chunk& chunk) override;
};