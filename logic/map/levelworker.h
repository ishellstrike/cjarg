#ifndef LEVELWORKER_H
#define LEVELWORKER_H
#include "sector.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include <glm/glm.hpp>

class LevelWorker
{
public:
    LevelWorker();
    ~LevelWorker();

    std::unordered_map<glm::vec2, *Sector> mem;
    Sector *getSector(const glm::vec2 &pos);
};

#endif // LEVELWORKER_H
