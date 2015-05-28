#include "wander.h"


Agent *Wander::instantiate() const
{
    Agent *w = new Wander;
    return w;
}

void Wander::deserialize(rapidjson::Value &val)
{

}

void Wander::Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l, const AgentOwner &owner)
{

}

void Wander::Init(const glm::vec3 &pos, const Level &l)
{

}
