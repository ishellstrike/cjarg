#include "logic/agents/gamepart.h"


Dynamic *Dynamic::instantiate() const
{
    Dynamic *dyn = new Dynamic();
    for(auto ag : agents)
    {
        dyn->agents.push_back(std::shared_ptr<Agent>(ag->instantiate()));
    }
    return dyn;
}

void Dynamic::Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner)
{
    for(std::shared_ptr<Agent> a : agents)
    {
        Agent &ag = *a;
        ag.Update(gt, pos, l, owner);
    }
}

bool Dynamic::isEmpty() const
{
    return agents.size() == 0;
}

std::string Dynamic::debugInfo() const
{
    std::stringstream ss;

    for(std::shared_ptr<Agent> ag : agents)
    {
        ss << "{" << ag->debugInfo() << "} ";
    }

    return ss.str();
}

std::string Dynamic::fullInfo() const
{
    std::stringstream ss;

    for(std::shared_ptr<Agent> ag : agents)
        ss << ag->fullInfo() << ". ";

    return ss.str();
}


Jid GameBase::id()
{
    return m_id;
}
