#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>

struct Chest : public Agent
{
    Chest();
    Chest(std::vector<Item> items_);

    std::vector<Item> items;
};

#endif // CHEST_H
