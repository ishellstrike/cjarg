#ifndef LEVEL_H
#define LEVEL_H
#include <unordered_map>
#include <glm/glm.hpp>
#include "sectormap.h"

class Level
{
public:
    Level();
    ~Level();

    SectorMap active;
};

#endif // LEVEL_H
