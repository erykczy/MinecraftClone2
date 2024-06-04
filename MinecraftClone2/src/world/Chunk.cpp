#include "Chunk.h"
#include "src/world/def/Blocks.h"
#include "src/world/def/BlockDef.h"

Chunk::Chunk(Level* level, const glm::ivec2& pos) : m_level{ level }, m_position { pos } {
	auto* air{ new BlockState{ Blocks::all[0]->getDefaultBlockState()}};
	air->m_users = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_WIDTH - 1;
	m_palette.push_back(air);
}

Chunk::~Chunk() {
	for (auto* state : m_palette) {
		delete state;
	}
}

BlockState* Chunk::getBlockWithin(const glm::ivec3& relPos) const {
	if (relPos.y < 0 || relPos.y >= CHUNK_HEIGHT) return nullptr;
	return m_palette[m_blocks[relPos.x][relPos.y][relPos.z]];
}