#include "chest.h"

Agent *Chest::instantiate() const
{
    Chest *chest = new Chest();
    return chest;
}

