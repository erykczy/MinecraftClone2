#pragma once

#include <vector>

class BlockDef;

namespace Blocks {
	extern std::vector<BlockDef*> all;

	void initialize();
	void destroy();
}
