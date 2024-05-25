#pragma once

#include "src/world/BlockDef.h"

template<typename T>
class OneTexBlockDef : public BlockDef<T> {
public:
	OneTexBlockDef() = default;
	constexpr OneTexBlockDef(t_id id, const char* allSideTexture) : BlockDef(id), m_texture{ allSideTexture } {

	}

	Texture2D* getTexture(Side side) override {
		return &m_texture;
	}

protected:
	Texture2D m_texture{};

};