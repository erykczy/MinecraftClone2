#pragma once

#include "src/world/BlockDef.h"

class OneTexBlockDef : public BlockDef {
public:
	OneTexBlockDef() = default;
	OneTexBlockDef(std::string_view name, t_id id, const char* allSideTexture) : BlockDef(name, id), m_texture{ allSideTexture } {

	}

	const Texture2D* getTexture(Side side) const override {
		return &m_texture;
	}

protected:
	Texture2D m_texture;

};