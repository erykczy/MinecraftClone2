#include "BasicLevelGenerator.h"
#include "src/world/def/Blocks.h"

void BasicLevelGenerator::generateChunk(Chunk& chunk)
{
	//glm::ivec3 chunkLevelPos{ chunk.getPosition().x * CHUNK_WIDTH, 0.0f, chunk.getPosition().y * CHUNK_WIDTH };
	for (int x = 0; x < CHUNK_WIDTH; ++x) {
		for (int z = 0; z < CHUNK_WIDTH; ++z) {
			for (int y = 0; y < 7; ++y) {
				chunk.setBlockWithin(glm::ivec3{ x, y, z }, Blocks::all[1]->getDefaultBlockState()); // TODO magic number
			}
			for (int y = 7; y < 10; ++y) {
				chunk.setBlockWithin(glm::ivec3{ x, y, z }, Blocks::all[2]->getDefaultBlockState()); // magic number
			}
			chunk.setBlockWithin(glm::ivec3{ x, 10, z }, Blocks::all[3]->getDefaultBlockState()); // magic number
		}
	}

	for (int x = 1; x < 15; ++x) {
		for (int z = 1; z < 15; ++z) {
			chunk.setBlockWithin(glm::ivec3{ x, 11, z }, Blocks::all[3]->getDefaultBlockState());
		}
	}
}
