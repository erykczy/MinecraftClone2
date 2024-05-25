#pragma once

#include "src/world/BlockState.h"
#include "src/world/BlockDef.h"

namespace Blocks {
	extern BlockDef<BlockState> air;
	extern BlockDef<BlockState> stone;
	extern BlockDef<BlockState> dirt;
	extern BlockDef<BlockState> grass_block;
	extern BlockDef<BlockState> null_block;
	extern BlockDef<BlockState> null_block2;

	void initialize();
}
