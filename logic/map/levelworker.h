#ifndef LEVELWORKER_H
#define LEVELWORKER_H
#include <glm/glm.hpp>
#include <unordered_map>
#include <glm/glm.hpp>
#include "sectormap.h"

class LevelWorker
{
public:
    LevelWorker();
    ~LevelWorker();

    SectorMap mem;
    Sector *getSector(const Point &pos);
};

#endif // LEVELWORKER_H
