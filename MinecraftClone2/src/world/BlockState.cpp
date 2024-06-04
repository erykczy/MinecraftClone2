#include "BlockState.h"
#include "src/world/def/Blocks.h"

BlockDef* BlockState::getBlockDef() const {
	return Blocks::all[blockId];
}