#pragma once

#include "src/world/Side.h"
#include "src/rendering/Texture2D.h"

using t_id = unsigned short;

class BlockDef {
public:
	BlockDef() = default;
	BlockDef(std::string_view name, t_id id) : m_name{ name }, m_blockId { id } {

	}
	virtual ~BlockDef() = default;

	virtual BlockState getDefaultBlockState() const { return BlockState{ m_blockId }; }
	virtual const Texture2D* getTexture(Side side) const { return nullptr; }

	t_id getBlockId() const { return m_blockId; }
	const std::string& getName() { return m_name; }

protected:
	std::string m_name{};
	t_id m_blockId{};

};