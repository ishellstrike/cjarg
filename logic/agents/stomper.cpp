#include "stomper.h"
#include "logic/map/level.h"

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
    l.change_at(pos, 2);
}

void Stomper::Init(const glm::vec3 &pos, const Level &l)
{

}
