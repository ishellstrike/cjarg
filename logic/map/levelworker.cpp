#include "levelworker.h"
#include <future>

LevelWorker::LevelWorker()
{
    //threads = std::thread([](){int i; ++i; return;}); //stub
}

LevelWorker::~LevelWorker()
{
}

Sector *LevelWorker::getSector(const Point &pos, std::shared_ptr<Material> mat, std::shared_ptr<BasicJargShader> &basic, int slice)
{

    SectorMap::iterator f = mem.find(pos);
    if(f == mem.end())
    {
        mem[pos] = std::make_shared<Sector>(pos);
        return nullptr;
    }
    auto s = f->second;

    if(s->state == Sector::EMPTY && !has_thread)
    {
        s->state = Sector::BUILDING;
        has_thread = true;
        threads = std::thread([&, mat, basic, s](){
            th ++;
            if(generator && !s->rebuilding)
                generator(s);
            has_thread = false;
            s->state = Sector::BUILDED;
            th --;
            return;
        });
        threads.detach();
        return nullptr;
    }

    return s->state == Sector::BUILDED || s->state == Sector::READY ? s.get() : nullptr;
}

void LevelWorker::SetGenerator(std::function<void(std::shared_ptr<Sector>)> gen)
{
    generator = gen;
}

volatile bool LevelWorker::has_thread = false;
volatile int LevelWorker::th = 0;

