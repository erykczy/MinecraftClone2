#pragma once

#include "src/world/def/BlockDef.h"

class TexBlockDef : public BlockDef {
public:
	TexBlockDef() = default;
	TexBlockDef(
		std::string_view name, t_id id, 
		std::string_view frontTex,
		std::string_view backTex,
		std::string_view upTex,
		std::string_view downTex,
		std::string_view rightTex,
		std::string_view leftTex
	) : BlockDef(name, id)
	{
		textures.reserve(6);
		textures.emplace_back(frontTex);
		textures.emplace_back(backTex);
		textures.emplace_back(upTex);
		textures.emplace_back(downTex);
		textures.emplace_back(rightTex);
		textures.emplace_back(leftTex);
	}

	const Texture2D* getTexture(int index) const override {
		return &textures[index];
	}
	RenderingType getRenderingType() const override { return RenderingType::CUBE; }

protected:
	std::vector<Texture2D> textures{};

};