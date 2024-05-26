#include "Chunk.h"
#include "src/world/Blocks.h"

Chunk::Chunk(const glm::ivec2& pos) : m_position{ pos } {
	auto* air{ new BlockState{ Blocks::all[0]->getDefaultBlockState()}};
	air->m_users = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_WIDTH - 1;
	m_palette.push_back(air);
}

Chunk::~Chunk() {
	for (auto* state : m_palette) {
		delete state;
	}
}

BlockState* Chunk::getBlock(const glm::ivec3& pos) const {
	// TODO check pos
	int relX{ pos.x - m_position.x };
	int relY{ pos.y };
	int relZ{ pos.z - m_position.y };
	if (relX < 0 || relX >= CHUNK_WIDTH) return nullptr;
	if (relY < 0 || relY >= CHUNK_HEIGHT) return nullptr;
	if (relZ < 0 || relZ >= CHUNK_WIDTH) return nullptr;
	return m_palette[m_blocks[pos.x][pos.y][pos.z]];
}