#ifndef LEVEL_H
#define LEVEL_H
#include <unordered_map>
#include <glm/glm.hpp>
#include "sector.h"
#include "sectormap.h"
#include "spritebatch.h"
#include "levelworker.h"

class Level
{
public:
    Level(LevelWorker &lw);
    ~Level();

    void Draw(SpriteBatch &sb);

    SectorMap active;
};

#endif // LEVEL_H
