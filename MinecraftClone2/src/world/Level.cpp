#include "Level.h"

Chunk& Level::addChunk(const glm::ivec2& pos) {
	return m_chunks.emplace(pos, pos).first->second;
}
