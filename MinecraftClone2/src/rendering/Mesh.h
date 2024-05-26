#pragma once
#include <vector>
#include <cassert>
#include "src/app/util/Debug.h"

class Mesh final {
public:
	std::vector<float> vertices{};
	std::vector<unsigned int> indicies{};

	Mesh() = default;
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indicies)
		: vertices{ vertices }
		, indicies{ indicies }
	{
		if (vertices.size() % 3 != 0) Debug::logger << "Invalid count of vertices values" << Debug::endError;
		if (indicies.size() % 3 != 0) Debug::logger << "Invalid count of indicies values" << Debug::endError;
	}

	int getSizeOfVertices() {
		static_assert(typeid(vertices) == typeid(std::vector<float>));
		return static_cast<int>(sizeof(float) * vertices.size());
	}

	int getSizeOfIndicies() {
		static_assert(typeid(indicies) == typeid(std::vector<unsigned int>));
		return static_cast<int>(sizeof(int) * indicies.size());
	}
};

static_assert(std::is_move_constructible<Mesh>::value);
static_assert(std::is_move_assignable<Mesh>::value);
static_assert(std::is_copy_constructible<Mesh>::value);
static_assert(std::is_copy_assignable<Mesh>::value);
