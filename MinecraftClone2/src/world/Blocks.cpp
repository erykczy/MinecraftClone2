#pragma once
#include "src/world/Blocks.h"


namespace Blocks {
	extern std::vector<BlockDef*> all{};

	void initialize() {
		all.push_back(new BlockDef("Air", 0));
		all.push_back(new OneTexBlockDef("Stone", 1, "resources/textures/block/stone.png"));
		all.push_back(new BlockDef("Dirt", 2));
		all.push_back(new BlockDef("Grass Block", 3));
		all.push_back(new BlockDef("Null Block 1", 1000));
		all.push_back(new BlockDef("Null Block 2", 1001));
	}

	void destroy() {
		for (auto* def : all) {
			delete def;
		}
	}
}