#ifndef WANDER_H
#define WANDER_H
#include "agent.h"

//!
//! \brief AI agent
//!
struct Wander : public Agent
{
    AGENT(Wander)

    Agent *instantiate() const;
    void deserialize(rapidjson::Value &val);

    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l);
    void Init(const glm::vec3 &pos, const Level &l);
    std::string fullInfo(){return "";}
    std::string debugInfo(){return "";}
};

#endif // WANDER_H
