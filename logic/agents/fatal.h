#ifndef FATAL_H
#define FATAL_H
#include "agent.h"
#include "rapidjson/document.h"

struct Organ : public Agent
{
    AGENT(Organ)

    std::vector<std::string> buffs;

    void deserialize(rapidjson::Value &val);
    Agent *instantiate() const;
    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l);
    void Init(const glm::vec3 &pos, const Level &l);
};

#endif // FATAL_H
