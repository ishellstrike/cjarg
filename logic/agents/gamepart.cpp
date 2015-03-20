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
