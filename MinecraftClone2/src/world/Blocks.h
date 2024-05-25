#pragma once

#include "src/world/BlockDef.h"
#include <vector>

namespace Blocks {
	extern std::vector<BlockDef*> all;

	void initialize();
	void destroy();
}
