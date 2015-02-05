#include "levelworker.h"
#include <future>

LevelWorker::LevelWorker()
{
    threads = std::async([](){int i; i++;}); //stub
}

LevelWorker::~LevelWorker()
{
}

Sector *LevelWorker::getSector(const Point &pos, std::shared_ptr<Material> mat, std::shared_ptr<BasicJargShader> &basic)
{
    SectorMap::iterator f = mem.find(pos);
    if(f == mem.end())
    {
        Sector *s = new Sector(pos);
        mem[pos] = std::unique_ptr<Sector>(s);
        return nullptr;
    }
    auto &s = f->second;

    if(s->mesh.Vertices.size() == 0 && s->state == Sector::EMPTY && !has_thread)
    {
        has_thread = true;
        threads.get();
        threads = std::async(std::launch::async, [&, mat, basic](){
            if(generator)
                generator(*s);
            s->Rebuild(mat, basic);
            LevelWorker::has_thread = false;
        });
        s->state = Sector::BUILDING;
        return nullptr;
    }
    if(s->state == Sector::UNBINDED)
    {
        s->mesh.ForgetBind();
        s->state = Sector::READY;
    }

    return s->state == Sector::READY ? s.get() : nullptr;
}

void LevelWorker::SetGenerator(std::function<void(Sector &)> gen)
{
    generator = gen;
}

bool LevelWorker::has_thread = false;

