#include "agent.h"



Agent *StaticAgent::instantiate() const
{
    return nullptr;
}


Agent::Agent()
{

}

Agent::Agent(const std::string &__s, int __id) :
    type(__s),
    id(__id)
{

}

Agent::~Agent()
{

}

Agent *Agent::instantiate() const
{
    return nullptr;
}

void Agent::deserialize(rapidjson::Value &val)
{

}
