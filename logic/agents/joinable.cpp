#include "joinable.h"

Agent *Joinable::instantiate() const
{
    Joinable *j = new Joinable();
    static int join(0);
    j->join_id = join++;
    return j;
}

void Joinable::deserialize(rapidjson::Value &val)
{

}

void Joinable::Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l, const AgentOwner &owner)
{

}

void Joinable::Init(const glm::vec3 &pos, const Level &l)
{
    auto n = l.neighbours(pos);
    auto th = l.block(pos); //this block
    for(Block *b : n)
    {
        if(b->id() == th->id() && b->parts)
        {
            Dynamic &d = *b->parts;
            Joinable *j = d.getAgent<Joinable>();
            if(j)
            {
                j->join_id = join_id;
            }
        }
    }
}
