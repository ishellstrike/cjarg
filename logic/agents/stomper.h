#ifndef STOMPER_H
#define STOMPER_H
#include "agent.h"

//!
//! \brief Behavior agent
//!
struct Stomper : public Agent
{
    AGENT(Stomper)

    Agent *instantiate() const override;
    void deserialize(rapidjson::Value &val) override;

    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l, const AgentOwner &owner) override;
    void Init(const glm::vec3 &pos, const Level &l) override;
    std::string fullInfo() override {return "";}
    std::string debugInfo() override {return "";}
};

#endif // STOMPER_H
