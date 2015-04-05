#ifndef COLONY_H
#define COLONY_H
#include "../entity/creature.h"
#include <vector>
#include <memory>
#include "../order.h"

struct Colony
{
    std::vector<std::shared_ptr<Creature>> team;
    OrderList orders;
};

#endif // COLONY_H
