#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>

class Chest : public Agent
{
public:
    Chest();
    Chest(std::vector<Item> items_);
    ~Chest();

    std::vector<Item> items;
};

#endif // CHEST_H
