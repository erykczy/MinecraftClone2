#pragma once

#include "src/world/Blocks.h"

class BlockDef;
using t_id = unsigned short;

class BlockState {
public:
	t_id blockId{};

	constexpr BlockState() = default;
	constexpr BlockState(t_id blockId) : blockId{ blockId } {}
	constexpr virtual ~BlockState() {}

	BlockState(const BlockState& source) { copy(source); }
	BlockState& operator=(const BlockState&) = delete;

	bool operator==(const BlockState& state) const {
		return isSame(state) && state.isSame(*this);
	}
	
	BlockDef* getBlockDef() const {
		return Blocks::all[blockId];
	}

	friend class Chunk;

protected:
	virtual bool isSame(const BlockState& state) const {
		return blockId == state.blockId;
	}

	virtual void copy(const BlockState& source) {
		blockId = source.blockId;
	}

private:
	unsigned short m_users{};

};