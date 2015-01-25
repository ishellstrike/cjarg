#ifndef LEVELWORKER_H
#define LEVELWORKER_H
#include <glm/glm.hpp>
#include <unordered_map>
#include <glm/glm.hpp>
#include "sectormap.h"
#include <functional>

class LevelWorker
{
public:
    LevelWorker();
    ~LevelWorker();

    Sector *getSector(const Point &pos);
    void SetGenerator(std::function<void(Sector&)> gen);

private:
    SectorMap mem;
    std::function<void(Sector&)> generator;
};

#endif // LEVELWORKER_H
