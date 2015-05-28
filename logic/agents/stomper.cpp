#include "stomper.h"




Agent *Stomper::instantiate() const
{
    Agent *s = new Stomper;
    return s;
}

void Stomper::deserialize(rapidjson::Value &val)
{

}

void Stomper::Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l, const AgentOwner &owner)
{

}

void Stomper::Init(const glm::vec3 &pos, const Level &l)
{

}
