#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>
#include "cereal/access.hpp"
#include "cereal/types/vector.hpp"

struct Chest : public Agent
{
    AGENT(Chest)

    std::vector<Item> items;

    Agent *instantiate() const;

    template<class Archive>
    void save(Archive &ar)  const
    {
        ar(CEREAL_NVP(items));
    }
};

#endif // CHEST_H
