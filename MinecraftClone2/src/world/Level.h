#pragma once
#include "Chunk.h"
#include <unordered_map>

// TODO
struct IVec2Hash
{
    std::size_t operator() (const glm::ivec2& v) const
    {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) << 1;
    }
};

class Level final {
public:
	Level() = default;

	Chunk& addChunk(const glm::ivec2& pos);

private:
	std::unordered_map<glm::ivec2, Chunk, IVec2Hash> m_chunks{};
};