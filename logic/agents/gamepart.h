#ifndef GAMEPART_H
#define GAMEPART_H
#include "agents.hpp"
#include <vector>
#include <memory>
#include <functional>

class Dynamic
{
public:
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
            a(agent->agent);
            return true;
        }
        return false;
    }

    template <typename T>
    void pushAgent(std::shared_ptr<T> agent)
    {
        agents.push_back(agent);
    }

    bool isEmpty()
    {
        return agents.size() == 0;
    }

private:
    std::vector<std::shared_ptr<Agent>> agents;
};

struct Static
{
    std::vector<std::shared_ptr<StaticAgent>> static_agents;
};

#endif // GAMEPART_H
