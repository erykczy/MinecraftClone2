#pragma once

using t_id = unsigned short;

class BlockState {
public:
	t_id blockId{};

	constexpr BlockState() = default;

	constexpr BlockState(t_id blockId) : blockId{ blockId } {

	}

	BlockState(const BlockState& source) {
		copy(source);
	}

	BlockState& operator=(const BlockState&) = delete;

	constexpr virtual ~BlockState() {

	}

	bool operator==(const BlockState& state) const {
		return isSame(state) && state.isSame(*this);
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