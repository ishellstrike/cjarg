#ifndef FURNANCE_H
#define FURNANCE_H
#include "agent.h"

struct Furnance : public Agent
{
    AGENT(Furnance)

    int temp = 100;

    Agent *instantiate() const;

    template<class Archive>
    void save(Archive &ar)  const
    {
        ar(CEREAL_NVP(temp));
    }
};

#endif // FURNANCE_H
