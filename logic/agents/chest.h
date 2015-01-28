#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include <vector>

class Chest : public Agent
{
public:
    Chest();
    Chest(std::vector<int> items_);
    ~Chest();

    std::vector<int> items;
};

#endif // CHEST_H
