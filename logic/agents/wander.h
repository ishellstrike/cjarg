#ifndef WANDER_H
#define WANDER_H
#include "agent.h"

//!
//! \brief AI agent
//!
struct Wander : public Agent
{
    AGENT(Wander)

    Agent *instantiate() const override;
    void deserialize(rapidjson::Value &val) override;

    void Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner) override;
    void Init(const glm::vec3 &pos, const Level &l) override;
    std::string fullInfo() override {return "";}
    std::string debugInfo() override {return "";}
};

#endif // WANDER_H
