#include "stompable.h"
#include "gamepart.h"

Agent *Stompable::instantiate() const
{
    Stompable *j = new Stompable();
    return j;
}

void Stompable::deserialize(rapidjson::Value &val)
{
    DESERIALIZE(NVP(afterstomp));
}

void Stompable::Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner)
{

}

void Stompable::Init(const glm::vec3 &pos, const Level &l)
{

}
