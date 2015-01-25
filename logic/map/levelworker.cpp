#include "levelworker.h"

LevelWorker::LevelWorker()
{

}

LevelWorker::~LevelWorker()
{

}

Sector *LevelWorker::getSector(const Point &pos)
{
    SectorMap::iterator f = mem.find(pos);
    if(f == mem.end())
    {
        Sector *s = new Sector(pos);
        mem[pos] = s;

        if(generator)
        {
            generator(*s);
        }

        return s;
    }
    return f->second;
}

void LevelWorker::SetGenerator(std::function<void(Sector &)> gen)
{
    generator = gen;
}

