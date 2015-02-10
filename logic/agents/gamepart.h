#ifndef GAMEPART_H
#define GAMEPART_H
#include "agent.h"
#include <vector>
#include <memory>

typedef int Jid;
typedef int Jtex;

struct Dynamic
{
    Dynamic();
    ~Dynamic();

    std::vector<std::shared_ptr<Agent>> agents;
    Dynamic *instantiate() const;
};

struct Static
{
    Static();
    ~Static();

    std::vector<std::shared_ptr<StaticAgent>> static_agents;
};

#endif // GAMEPART_H
