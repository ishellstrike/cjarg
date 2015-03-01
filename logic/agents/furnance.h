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
};

#endif // FURNANCE_H
