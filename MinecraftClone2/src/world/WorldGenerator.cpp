#include "WorldGenerator.h"
#include "src/world/Chunk.h"
#include "src/world/Blocks.h"

void WorldGenerator::generateChunk(Chunk& chunk)
{
	glm::ivec3 chunkPos{ chunk.getPosition().x, chunk.getPosition().y, 0.0f};
	for (int x = 0; x < 16; ++x) {
		for (int z = 0; z < 16; ++z) {
			for (int y = 0; y < 57; ++y) {
				chunk.setBlock(chunkPos + glm::ivec3{ x, y, z }, Blocks::stone.getDefaultBlockState());
			}
			for (int y = 57; y < 60; ++y) {
				chunk.setBlock(chunkPos + glm::ivec3{ x, y, z }, Blocks::dirt.getDefaultBlockState());
			}
			chunk.setBlock(chunkPos + glm::ivec3{ x, 60, z }, Blocks::grass_block.getDefaultBlockState());
		}
	}
}