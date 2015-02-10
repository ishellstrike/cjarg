#include "levelworker.h"
#include <future>

LevelWorker::LevelWorker()
{
    //threads = std::thread([](){int i; i++; return;}); //stub
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

    if(s->mesh.Vertices.size() == 0 && s->state == Sector::EMPTY)
    {
        threads = std::thread([&, mat, basic](){
            //static std::mutex lock;
            //lock.lock();

            if(generator)
                generator(*s);
            s->Rebuild(mat, basic);
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            //lock.unlock();
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
    }

    return s->state == Sector::READY ? s.get() : nullptr;
}

void LevelWorker::SetGenerator(std::function<void(Sector &)> gen)
{
    generator = gen;
}

volatile bool LevelWorker::has_thread = false;

