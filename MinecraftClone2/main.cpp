#include "src/app/Program.h"
#include <iostream>

int main() {
	try {
		Program program{};
		program.startProgramLoop();
	}
	catch (std::runtime_error err) {
		std::cerr << err.what() << std::endl;
	}

	return 0;
}