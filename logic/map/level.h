#ifndef LEVEL_H
#define LEVEL_H
#include <unordered_map>
#include <glm/glm.hpp>
#include "sector.h"

class Level
{
public:
    Level();
    ~Level();

    std::unordered_map<glm::vec2, *Sector> active;
};

#endif // LEVEL_H
