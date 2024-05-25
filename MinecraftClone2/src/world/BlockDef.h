#pragma once

#include "src/world/Side.h"
#include "src/rendering/Texture2D.h"

using t_id = unsigned short;

template<typename T>
class BlockDef {
public:
	BlockDef() = default;
	constexpr BlockDef(t_id id) : m_blockId{ id } {

	}
	virtual ~BlockDef() = default;

	virtual T getDefaultBlockState() const { return T{ m_blockId }; }
	virtual Texture2D* getTexture(Side side) const { return nullptr; }

	t_id getBlockId() const { return m_blockId; }

protected:
	t_id m_blockId{};

};