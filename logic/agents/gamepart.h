#ifndef GAMEPART_H
#define GAMEPART_H
#include "agents.h"
#include <vector>
#include <memory>
#include <functional>

struct Dynamic
{
    Dynamic();
    ~Dynamic();

    std::vector<std::shared_ptr<Agent>> agents;
    Dynamic *instantiate() const;

    template <typename T>
    T *getAgent()
    {
        for(auto a : agents)
        {
            Agent &agent = *a;
            if(agent.id == Agent::typeid_for<T>())
                return static_cast<T*>(&agent);
        }
        return nullptr;
    }

    template <typename T>
    bool forAgent(std::function<void(T*)> a)
    {
        T *agent = getAgent<T>();
        if(agent)
        {
            a(agent-> agent);
            return true;
        }
        return false;
    }
};

struct Static
{
    Static();
    ~Static();

    std::vector<std::shared_ptr<StaticAgent>> static_agents;
};

#endif // GAMEPART_H
