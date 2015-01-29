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
    Level(LevelWorker &lw_);
    ~Level();

    void Draw(SpriteBatch &sb, const glm::vec3 &cam);
    void Preload(Point p, int r);

    Block *block(const Point3 &p);
    Block *block(const glm::vec3 &p);

    unsigned char ground(const glm::vec3 &p);

    float zoom = 32;

    SectorMap active;
    LevelWorker &lw;
};

#endif // LEVEL_H
