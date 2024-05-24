#pragma once

#include "src/world/BlockState.h"

namespace Blocks {
	inline constexpr BlockState air{ 0 };
	inline constexpr BlockState stone{ 1 };
	inline constexpr BlockState dirt{ 2 };
	inline constexpr BlockState grass_block{ 3 };
	inline constexpr BlockState null_block{ 1000 };
}
