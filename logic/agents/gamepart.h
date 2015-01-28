#ifndef GAMEPART_H
#define GAMEPART_H
#include "agent.h"
#include <vector>

#define AGENT(container, type) { auto part = container->getAgent<type>(); if (part) {
#define AGENTEND() }}

class GamePart
{
public:
    GamePart();

    template <typename T>
    T *getAgent(){
        for(const Caster &c: agents)
        {
            if(c.is<T>())
                return &c.as<T>();
        }
        return nullptr;
    }

    std::vector<Caster> agents;
};

#endif // GAMEPART_H
