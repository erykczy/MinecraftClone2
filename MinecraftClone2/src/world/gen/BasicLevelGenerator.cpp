#include "BasicLevelGenerator.h"
#include "src/world/def/Blocks.h"
#include "libraries/PerlinNoise.hpp"

void BasicLevelGenerator::generateChunk(Chunk& chunk)
{
	const siv::PerlinNoise::seed_type seed{ 2346780u };
	const siv::PerlinNoise perlinNoise{ seed };
	const float scale{ 0.1f };

	//glm::ivec3 chunkLevelPos{ chunk.getPosition().x * CHUNK_WIDTH, 0.0f, chunk.getPosition().y * CHUNK_WIDTH };
	for (int x = 0; x < CHUNK_WIDTH; ++x) {
		for (int z = 0; z < CHUNK_WIDTH; ++z) {
			auto perlin{ perlinNoise.noise2D_01((chunk.getPosition().x * CHUNK_WIDTH + x) * scale, (chunk.getPosition().y * CHUNK_WIDTH + z) * scale)};
			int height{ 10 + static_cast<int>(perlin * 5.0f) };
			for (int y = 0; y < height-3; ++y) {
				chunk.setBlockWithin(glm::ivec3{ x, y, z }, Blocks::all[1]->getDefaultBlockState()); // TODO magic number
			}
			for (int y = height-3; y < height; ++y) {
				chunk.setBlockWithin(glm::ivec3{ x, y, z }, Blocks::all[2]->getDefaultBlockState()); // magic number
			}
			chunk.setBlockWithin(glm::ivec3{ x, height, z }, Blocks::all[3]->getDefaultBlockState()); // magic number
		}
	}
}
