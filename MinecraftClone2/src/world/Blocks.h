#pragma once

#include "src/world/BlockState.h"
#include "src/world/BlockDef.h"
#include "src/world/OneTexBlockDef.h"
#include <vector>

namespace Blocks {
	extern std::vector<BlockDef*> all;

	void initialize();
	void destroy();
}
