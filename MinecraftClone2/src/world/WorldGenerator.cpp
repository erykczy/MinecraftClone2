#include "WorldGenerator.h"
#include "src/world/Chunk.h"
#include "src/world/Blocks.h"

void WorldGenerator::generateChunk(Chunk& chunk)
{
	glm::ivec3 chunkPos{ chunk.getPosition().x, chunk.getPosition().y, 0.0f};
	for (int x = 0; x < 16; ++x) {
		for (int z = 0; z < 16; ++z) {
			for (int y = 0; y < 7; ++y) {
				chunk.setBlock(chunkPos + glm::ivec3{ x, y, z }, Blocks::all[1]->getDefaultBlockState()); // TODO magic number
			}
			for (int y = 7; y < 10; ++y) {
				chunk.setBlock(chunkPos + glm::ivec3{ x, y, z }, Blocks::all[2]->getDefaultBlockState()); // magic number
			}
			chunk.setBlock(chunkPos + glm::ivec3{ x, 10, z }, Blocks::all[3]->getDefaultBlockState()); // magic number
		}
	}

	for (int x = 1; x < 15; ++x) {
		for (int z = 1; z < 15; ++z) {
			chunk.setBlock(chunkPos + glm::ivec3{ x, 11, z }, Blocks::all[3]->getDefaultBlockState());
		}
	}
}