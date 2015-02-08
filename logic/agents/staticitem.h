#ifndef STATICITEM_H
#define STATICITEM_H
#include <string>
#include "agent.h"

struct StaticItemBase : public StaticAgent
{
    unsigned short weight;
    std::string description;
    std::string name;
};

#endif // STATICITEM_H
