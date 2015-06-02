#ifndef FURNANCE_H
#define FURNANCE_H
#include "agent.h"
#include "rapidjson/document.h"

struct Furnance : public Agent
{
    AGENT(Furnance)

    int temp = 100;

    Agent *instantiate() const;
    void deserialize(rapidjson::Value &val);

    void Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner);
    void Init(const glm::vec3 &pos, const Level &l);
    std::string fullInfo(){return "";}
    std::string debugInfo(){return "";}
};

#endif // FURNANCE_H
