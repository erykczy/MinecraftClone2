#pragma once
#include "src/world/Chunk.h"
#include "src/event/ILevelEventListener.h"
#include <unordered_map>
#include <memory>

class LevelGenerator;

// TODO
struct IVec2Hash
{
    std::size_t operator() (const glm::ivec2& v) const
    {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) << 1;
    }
};

class Level final : public IEventSender<ILevelEventListener> {
public:
    LevelGenerator* levelGenerator{};

    Level(LevelGenerator* generator) : levelGenerator{ generator } {};

	Chunk& addChunk(const glm::ivec2& pos);
    Chunk* getChunk(const glm::ivec2& pos, bool genChunk = true);
    Chunk* getChunkOfBlock(const glm::ivec3& blockPos, bool getChunk = true);
    glm::ivec3 levelSpaceToChunkSpace(const glm::ivec3& levelPos);
    BlockState* getBlock(const glm::ivec3& pos, bool genChunk = true);
    bool isAir(const glm::ivec3& pos, bool genChunk = true);

    template<typename T>
    void setBlock(const glm::ivec3& pos, const T& newBlockState);

private:
	std::unordered_map<glm::ivec2, Chunk, IVec2Hash> m_chunks{};
};

template<typename T>
void Level::setBlock(const glm::ivec3& pos, const T& newBlockState) {
    auto& chunk{ *getChunkOfBlock(pos, true) };
    chunk.setBlockWithin(levelSpaceToChunkSpace(pos), newBlockState);
}