#include "chest.h"

Chest::Chest()
{

}

Chest::Chest(std::vector<Item *> items_)
{
    items = items_;
}

Agent *Chest::instantiate() const
{
    Chest *chest = new Chest();
    return chest;
}

