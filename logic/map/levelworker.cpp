#include "levelworker.h"
#include <future>

LevelWorker::LevelWorker()
{
    //threads = std::thread([](){int i; ++i; return;}); //stub
}

LevelWorker::~LevelWorker()
{
}

Sector *LevelWorker::getSector(const Point &pos, std::shared_ptr<Material> mat, std::shared_ptr<BasicJargShader> &basic)
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
        has_thread = true;
        threads = std::thread([&, mat, basic, s](){
            th ++;
            if(generator && !s->rebuilding)
                generator(s);
            s->Rebuild(mat, basic);
            has_thread = false;
            th --;
            return;
        });
        threads.detach();
        s->state = Sector::BUILDING;
        return nullptr;
    }
    if(s->state == Sector::UNBINDED)
    {
        s->mesh.ForgetBind();
        s->state = Sector::READY;
        if(!s->rebuild_later)
            s->rebuilding = false;
        else
            s->state = Sector::EMPTY;
        s->rebuild_later = false;
    }

    return s->state == Sector::READY ? s.get() : nullptr;
}

void LevelWorker::SetGenerator(std::function<void(std::shared_ptr<Sector>)> gen)
{
    generator = gen;
}

volatile bool LevelWorker::has_thread = false;
volatile int LevelWorker::th = 0;

