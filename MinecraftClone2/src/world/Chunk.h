#pragma once

#include "src/world/BlockState.h"
#include "src/event/IEventSender.h"
#include "src/event/IChunkEventListener.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

class Level;

static_assert(sizeof(short) == 2);
inline constexpr int CHUNK_WIDTH = 16;
inline constexpr int CHUNK_HEIGHT = 256;

class Chunk final : public IEventSender<IChunkEventListener> {
public:
	Chunk() = default;
	Chunk(Level* level, const glm::ivec2& pos);

	~Chunk();

	glm::ivec2 getPosition() const { return m_position; }
	Level* getLevel() const { return m_level; }

	BlockState* getBlockWithin(const glm::ivec3& pos) const;

	template<typename T>
	void setBlockWithin(const glm::ivec3& relPos, const T& newBlockState);

	friend class ChunkModel;

private:
	Level* m_level{};
	glm::ivec2 m_position{};
	std::vector<BlockState*> m_palette{};
	short m_blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH]{};
};

template<typename T>
void Chunk::setBlockWithin(const glm::ivec3& relPos, const T& newBlockState) {
	glm::ivec3 worldPos{ relPos.x + m_position.x * CHUNK_WIDTH, relPos.y, relPos.z + m_position.y * CHUNK_WIDTH };
	if (relPos.y < 0 && relPos.y >= CHUNK_HEIGHT) {
		Debug::logger << "Position outside the chunk" << Debug::endError;
		return;
	}
	// remove existing blockState
	auto* existingBlockState{ getBlockWithin(relPos) };
	if (existingBlockState->m_users == 0) {
		short index{ m_blocks[relPos.x][relPos.y][relPos.z] };
		m_palette.erase(m_palette.begin() + index);
		delete existingBlockState;

		// update existing indicies
		for (int x = 0; x < CHUNK_WIDTH; ++x) {
			for (int z = 0; z < CHUNK_WIDTH; ++z) {
				for (int y = 0; y < CHUNK_HEIGHT; ++y) {
					if (m_blocks[getPosition().x + x][y][getPosition().y + z] > index) {
						--m_blocks[getPosition().x + x][y][getPosition().y + z];
					}
				}
			}
		}
	}
	else {
		--existingBlockState->m_users;
	}

	// get/add blockState from palette
	bool found{ false };
	bool foundEmptyPlace{ false };
	std::size_t index{ m_palette.size() };
	for (std::size_t i{ 0 }; i < m_palette.size(); ++i) {
		if (m_palette[i]) {
			if (*m_palette[i] == newBlockState) {
				found = true;
				index = i;
				break;
			}
		}
		else if (!foundEmptyPlace) {
			foundEmptyPlace = true;
			index = i;
		}
	}
	if (found) {
		++m_palette[index]->m_users;
	}
	else {
		if (foundEmptyPlace) {
			m_palette[index] = new T{ newBlockState };
		}
		else {
			m_palette.push_back(new T{ newBlockState });
		}
	}
	// set pointer
	m_blocks[relPos.x][relPos.y][relPos.z] = static_cast<unsigned short>(index);
	notifyListeners([this, &worldPos](IChunkEventListener* listener) { listener->onBlockChanged(*this, worldPos); });
}