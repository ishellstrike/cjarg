#ifndef GAMEPART_H
#define GAMEPART_H
#include "agent.h"
#include <vector>
#include "caster.h"

#define STATIC(container, type) { auto part = container->getStatic<type>(); if (part) {
#define DYNAMIC(container, type) { auto part = container->getDynamic<type>(); if (part) {
#define ACTIVE(container, type) { auto part = container->getActive<type>(); if (part) {
#define END() }}

struct Dynamic
{
    Dynamic();
    ~Dynamic();

    std::vector<Agent*> agents;
    Dynamic *instantiate() const;
};

struct Static
{
    Static();
    ~Static();

    std::vector<StaticAgent*> static_agents;
};

#endif // GAMEPART_H
