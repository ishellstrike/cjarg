#ifndef SERIZLIZE_TESTS_H
#define SERIZLIZE_TESTS_H
#include "catch.hpp"
#include "../logic/agents/gamepart.h"
#include "rapidjson/document.h"
#include <memory>

TEST_CASE( "Deserialize templates test", "[deserialize]" ) {

    SECTION("basic deserialize template (all types at once)") {
        rapidjson::Document d;
        d.Parse<0>(R"xxx(
                   {
                       "_string":"123",
                       "_int":123,
                       "_float":1.23,
                       "_bool":true
                   })xxx");

        std::string _string;
        int _int;
        float _float;
        bool _bool;

        const rapidjson::Value &val = d;

        DESERIALIZE(NVP(_string), NVP(_int), NVP(_float), NVP(_bool));

        REQUIRE(_string == "123");
        REQUIRE(_int == 123);
        REQUIRE(_float == 1.23f);
        REQUIRE(_bool == true);
    }
}

#endif // SERIZLIZE_TESTS_H

