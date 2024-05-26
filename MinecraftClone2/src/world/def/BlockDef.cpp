#include "BlockDef.h"

#include "src/world/BlockState.h"

BlockState BlockDef::getDefaultBlockState() const {
	return BlockState{ m_blockId };
}