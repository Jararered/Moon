#pragma once

#include <string>

// A simple type alias
using EntityID = unsigned long long;

// Used to define the size of arrays later on
const EntityID MAX_ENTITIES = 10000;

struct Entity
{
    std::string Name;
    EntityID ID;
};