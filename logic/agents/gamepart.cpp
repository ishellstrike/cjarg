#include "logic/agents/gamepart.h"
Static::~Static()
{
    for(StaticAgent *a: static_agents)
    {
        delete a;
    }
}


Static::Static()
{

}


Dynamic::Dynamic()
{

}


Dynamic::~Dynamic()
{
    for(Agent *a: agents)
    {
        delete a;
    }
}

Dynamic *Dynamic::instantiate() const
{
    Dynamic *dyn = new Dynamic();
    for(Agent *ag : agents)
    {
        dyn->agents.push_back(ag->instantiate());
    }
    return dyn;
}
