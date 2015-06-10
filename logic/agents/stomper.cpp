#include "stomper.h"
#include "logic/map/level.h"
#include "stompable.h"

Agent *Stomper::instantiate() const
{
    Agent *s = new Stomper;
    return s;
}

void Stomper::deserialize(rapidjson::Value &val)
{

}

void Stomper::Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner)
{
    if(pos.z >= 31) return;
    Block *b = l.block(pos - glm::vec3(0,0,1)).get();
    if(b)
    {
        Dynamic *d = b->parts.get();
        if(d)
        {
            Stompable *s = d->getAgent<Stompable>();
            if(s)
            {
                int a = 2;
                a = 2;
            }
        }
    }
}

void Stomper::Init(const glm::vec3 &pos, const Level &l)
{

}
