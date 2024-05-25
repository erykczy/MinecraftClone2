#pragma once
#include "src/world/Blocks.h"
#include "src/world/OneTexBlockDef.h"
#include "src/world/TexBlockDef.h"

std::string blockTextures{ "resources/textures/block/" };

namespace Blocks {
	extern std::vector<BlockDef*> all{};

	std::string loc(std::string_view path) {
		return blockTextures + path.data();
	}

	void initialize() {
		all.push_back(new BlockDef("Air", 0));
		all.push_back(new OneTexBlockDef("Stone", 1, loc("stone.png")));
		all.push_back(new OneTexBlockDef("Dirt", 2, loc("dirt.png")));
		all.push_back(new TexBlockDef("Grass Block", 3, loc("grass_block_side.png"), loc("grass_block_side.png"), loc("grass_block_top.png"), loc("dirt.png"), loc("grass_block_side.png"), loc("grass_block_side.png")));
		all.push_back(new BlockDef("Null Block 1", 1000));
		all.push_back(new BlockDef("Null Block 2", 1001));
	}

	void destroy() {
		for (auto* def : all) {
			delete def;
		}
	}
}