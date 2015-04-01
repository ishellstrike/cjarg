#ifndef SERIZLIZE_TESTS_H
#define SERIZLIZE_TESTS_H
#include "catch.hpp"
#include "../logic/agents/gamepart.h"
#include "rapidjson/document.h"
#include <memory>

TEST_CASE( "Deserialize templates test", "[deserialize]" ) {

    SECTION("basic deserialize template") {
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

    SECTION("vec deserialize template") {
        rapidjson::Document d;
        d.Parse<0>(R"xxx(
                   {
                       "_vec3":[1,2,3],
                       "_vec2":[1,2],
                       "_vec4":[1,2,3,4]
                   })xxx");

        glm::vec2 _vec2;
        glm::vec3 _vec3;
        glm::vec4 _vec4;

        const rapidjson::Value &val = d;

        DESERIALIZE(NVP(_vec2), NVP(_vec3), NVP(_vec4));

        CHECK(_vec2 == glm::vec2(1.f, 2.f));
        CHECK(_vec3 == glm::vec3(1.f, 2.f, 3.f));
        CHECK(_vec4 == glm::vec4(1.f, 2.f, 3.f, 4.f));
    }

    SECTION("vec deserialize template error") {
        rapidjson::Document d;
        d.Parse<0>(R"xxx(
                   {
                       "_vec3":[1,2],
                       "_vec2":[1,2,3],
                       "_vec4":[1,2,"3",4]
                   })xxx");

        glm::vec2 _vec2;
        glm::vec3 _vec3;
        glm::vec4 _vec4;

        const rapidjson::Value &val = d;

        REQUIRE_THROWS_AS(DESERIALIZE(NVP(_vec2)), std::invalid_argument);
        REQUIRE_THROWS_AS(DESERIALIZE(NVP(_vec3)), std::invalid_argument);
        REQUIRE_THROWS_AS(DESERIALIZE(NVP(_vec4)), std::invalid_argument);
    }

    SECTION("vector deserialize template") {
        rapidjson::Document d;
        d.Parse<0>(R"xxx(
                   {
                       "_some_vector":[1,2,3,4,5],
                       "_some_vector_string":["q","w","e","r","qwer"]
                   })xxx");

        std::vector<int> _some_vector;
        std::vector<std::string>_some_vector_string;

        const rapidjson::Value &val = d;

        DESERIALIZE(NVP(_some_vector), NVP(_some_vector_string));

        REQUIRE(_some_vector.size() == 5);
        REQUIRE(_some_vector_string.size() == 5);
        CHECK(_some_vector == std::vector<int>({1,2,3,4,5}));
        CHECK(_some_vector_string == std::vector<std::string>({"q","w","e","r","qwer"}));
    }

    SECTION("vector deserialize template error") {
        rapidjson::Document d;
        d.Parse<0>(R"xxx(
                   {
                       "_some_vector":[1,2,3,"4",5],
                       "_some_vector_string":["q",1,"e","r","qwer"]
                   })xxx");

        std::vector<int> _some_vector;
        std::vector<std::string>_some_vector_string;

        const rapidjson::Value &val = d;

        REQUIRE_THROWS_AS(DESERIALIZE(NVP(_some_vector)), std::invalid_argument);
        REQUIRE_THROWS_AS(DESERIALIZE(NVP(_some_vector_string)), std::invalid_argument);
    }
}

#endif // SERIZLIZE_TESTS_H

