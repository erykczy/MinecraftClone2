#include "Blocks.h"

namespace Blocks {
	extern BlockDef<BlockState> air{};
	extern BlockDef<BlockState> stone{};
	extern BlockDef<BlockState> dirt{};
	extern BlockDef<BlockState> grass_block{};
	extern BlockDef<BlockState> null_block{};
	extern BlockDef<BlockState> null_block2{};

	void initialize() {
		air = { 0 };
		stone = { 1 };
		dirt = { 2 };
		grass_block = { 3 };
		null_block = { 1000 };
		null_block2 = { 1001 };
	}
}