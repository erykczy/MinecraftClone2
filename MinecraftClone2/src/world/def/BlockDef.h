#pragma once

#include "src/rendering/Texture2D.h"

class BlockState;
using t_id = unsigned short;

class BlockDef {
public:
	enum class RenderingType {
		NONE,
		CUBE
	};

	BlockDef() = default;
	BlockDef(std::string_view name, t_id id) : m_name{ name }, m_blockId { id } {

	}
	virtual ~BlockDef() = default;

	virtual BlockState getDefaultBlockState() const;
	virtual const Texture2D* getTexture(int index) const { return nullptr; }
	virtual RenderingType getRenderingType() const { return RenderingType::NONE; }

	t_id getBlockId() const { return m_blockId; }
	const std::string& getName() { return m_name; }

protected:
	std::string m_name{};
	t_id m_blockId{};

};