#ifndef LEVELWORKER_H
#define LEVELWORKER_H
#include <glm/glm.hpp>
#include <unordered_map>
#include <glm/glm.hpp>
#include "sectormap.h"
#include <functional>
#include <future>
#include <list>

class LevelWorker
{
public:
    LevelWorker();
    ~LevelWorker();

    Sector *getSector(const Point &pos, std::shared_ptr<Material> mat, std::shared_ptr<BasicJargShader> &basic);
    void SetGenerator(std::function<void(Sector&)> gen);
    SectorMap mem;
private:

    std::function<void(Sector&)> generator;
    std::thread threads;
    volatile static bool has_thread;
};

#endif // LEVELWORKER_H
