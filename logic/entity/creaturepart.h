#ifndef CREATUREPART_H
#define CREATUREPART_H
#include <string>
#include <vector>
#include <memory>
#include "../agents/agent.h"

struct CreaturePart
{
    Jid item_id;
    std::vector<std::unique_ptr<CreaturePart>> subparts;
};

#endif // CREATUREPART_H
