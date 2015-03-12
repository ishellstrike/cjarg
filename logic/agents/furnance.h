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

public:
    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l);
    void Init(const glm::vec3 &pos, const Level &l);
};

#endif // FURNANCE_H
