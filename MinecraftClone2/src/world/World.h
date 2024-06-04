#pragma once
#include "src/world/Level.h"

class World {
public:
	World(LevelGenerator* overworldGenerator) : overworld{ overworldGenerator } {}

	Level overworld;
};