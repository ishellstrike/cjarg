#ifndef GAMEPART_H
#define GAMEPART_H
#include "agent.h"
#include <vector>
#include "caster.h"

#define STATIC(container, type) { auto part = container->getStatic<type>(); if (part) {
#define DYNAMIC(container, type) { auto part = container->getDynamic<type>(); if (part) {
#define ACTIVE(container, type) { auto part = container->getActive<type>(); if (part) {
#define END() }}

class Dynamic
{
public:
    Dynamic();
    ~Dynamic();

    std::vector<Agent*> agents;
};

class Static
{
public:
    Static();
    ~Static();

    std::vector<StaticAgent*> static_agents;
};

#endif // GAMEPART_H
