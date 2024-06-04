#pragma once

class Chunk;

class ILevelEventListener {
public:
	virtual ~ILevelEventListener() = default;

	virtual void onChunkAdded(Level& level, Chunk& chunk) {}
};