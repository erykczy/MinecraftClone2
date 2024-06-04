#include "Level.h"
#include "src/world/gen/LevelGenerator.h"

Chunk& Level::addChunk(const glm::ivec2& pos) {
	auto& chunk{ m_chunks.try_emplace(pos, this, pos).first->second };
	levelGenerator->generateChunk(chunk);
	notifyListeners([this, &chunk](ILevelEventListener* listener) { listener->onChunkAdded(*this, chunk); });
	return chunk;
}

Chunk* Level::getChunk(const glm::ivec2& pos, bool genChunk)
{
	if (!m_chunks.contains(pos)) {
		if (genChunk)
			addChunk(pos);
		else
			return nullptr;
	}
	return &m_chunks[pos];
}

Chunk* Level::getChunkOfBlock(const glm::ivec3& blockPos, bool genChunk)
{
	return getChunk({ floor(blockPos.x / static_cast<float>(CHUNK_WIDTH)), floor(blockPos.z / static_cast<float>(CHUNK_WIDTH)) }, genChunk);
}

glm::ivec3 Level::levelSpaceToChunkSpace(const glm::ivec3& levelPos)
{
	int x{ levelPos.x % CHUNK_WIDTH };
	int z{ levelPos.z % CHUNK_WIDTH };
	if (x < 0) x = CHUNK_WIDTH + x;
	if (z < 0) z = CHUNK_WIDTH + z;
	return glm::ivec3{ x, levelPos.y, z };
}

BlockState* Level::getBlock(const glm::ivec3& pos, bool genChunk)
{
	auto* chunk{ getChunkOfBlock(pos, genChunk) };
	if (!chunk) return nullptr;
	return chunk->getBlockWithin(levelSpaceToChunkSpace(pos));
}

bool Level::isAir(const glm::ivec3& pos, bool genChunk)
{
	auto* res{ getBlock(pos, genChunk) };
	return !res || res->blockId == 0;
}
