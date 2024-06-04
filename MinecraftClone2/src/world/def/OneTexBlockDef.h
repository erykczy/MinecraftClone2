#pragma once

#include "src/world/def/BlockDef.h"
#include "src/rendering/Texture2D.h"

class OneTexBlockDef : public BlockDef {
public:
	OneTexBlockDef() = default;
	OneTexBlockDef(std::string_view name, t_id id, std::string_view allSideTexture) : BlockDef(name, id), m_texture{ allSideTexture } {

	}

	const Texture2D* getTexture(int index) const override {
		return &m_texture;
	}
	RenderingType getRenderingType() const override { return RenderingType::CUBE; }

protected:
	Texture2D m_texture;

};