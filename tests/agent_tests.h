#ifndef AGENT_TESTS_H
#define AGENT_TESTS_H
#include "catch.hpp"
#include "../logic/agents/gamepart.h"
#include "../logic/agents/agent.h"
#include "../logic/agents/chest.h"
#include <memory>

TEST_CASE( "Dynamic part tests", "[dynamic]" ) {

    Dynamic d;

    SECTION("add agent") {
        d.pushAgent(std::make_shared<Chest>());
        REQUIRE(d.isEmpty() == false);
    }

    SECTION("type id") {
        Chest c;
        REQUIRE(c.id == Agent::typeid_for<Chest>());
    }

    SECTION("get agent by type") {
        d.pushAgent(std::make_shared<Chest>());
        Chest *c = d.getAgent<Chest>();
        REQUIRE(c != nullptr);
        REQUIRE(c->id == Agent::typeid_for<Chest>());
    }

    SECTION("specific agent access") {
        d.pushAgent(std::make_shared<Chest>());
        Chest *c = d.getAgent<Chest>();
        REQUIRE(c != nullptr);

        c->items.push_back(std::unique_ptr<Item>(new Item));

        REQUIRE(c->id == Agent::typeid_for<Chest>());
    }
}

#endif // AGENT_TESTS_H

