#ifndef SCHEME_TESTS_H
#define SCHEME_TESTS_H
#include "catch.hpp"
#include "logic/map/scheme.h"

TEST_CASE( "Scheme tests", "[scheme]" ) {

SECTION("setter 3x3") {
        Scheme s;
        s.Set({{1,2,3},
               {4,5,6},
               {7,8,9}});

        CHECK(s.data[0][0] == 1);
        CHECK(s.data[0][1] == 2);
        CHECK(s.data[0][2] == 3);
        CHECK(s.data[1][1] == 5);
        CHECK(s.data[2][2] == 9);
    }

SECTION("setter 3x4") {
        Scheme s;
        s.Set({{1,2,3,11},
               {4,5,6,12},
               {7,8,9,13}});

        CHECK(s.data[0][3] == 11);
        CHECK(s.data[2][3] == 13);
    }

SECTION("transpose 3x3") {
        Scheme s;
        s.Set({{1,2,3},
               {4,5,6},
               {7,8,9}});

        Scheme target;
        target.Set({{1,4,7},
                    {2,5,8},
                    {3,6,9}});
        s.Transpose();
        CHECK(s.data == target.data);
    }

SECTION("transpose 3x4") {
        Scheme s;
        s.Set({{1,2,3,11},
               {4,5,6,12},
               {7,8,9,13}});

        Scheme target;
        target.Set({{ 1, 4, 7},
                    { 2, 5, 8},
                    { 3, 6, 9},
                    {11,12,13}});
        s.Transpose();
        CHECK(s.data == target.data);

        Scheme target_2;
        target_2.Set({{1,2,3,11},
                      {4,5,6,12},
                      {7,8,9,13}});
        s.Transpose();
        REQUIRE(s.data == target_2.data);
    }

SECTION("rotate cw") {
        Scheme s;
        s.Set({{1,2,3},
               {4,5,6},
               {7,8,9}});

        Scheme target;
        target.Set({{7,4,1},
                    {8,5,2},
                    {9,6,3}});
        s.RotateCW();
        CHECK(s.data == target.data);
    }

SECTION("rotate ccw") {
        Scheme s;
        s.Set({{1,2,3},
               {4,5,6},
               {7,8,9}});

        Scheme target;
        target.Set({{3,6,9},
                    {2,5,8},
                    {1,4,7}});
        s.RotateCCW();
        CHECK(s.data == target.data);
    }

SECTION("mirror x 3x3") {
        Scheme s;
        s.Set({{1,2,3},
               {4,5,6},
               {7,8,9}});

        Scheme target;
        target.Set({{7,8,9},
                    {4,5,6},
                    {1,2,3}});
        s.MirrorX();
        CHECK(s.data == target.data);
    }

SECTION("mirror x 3x4") {
        Scheme s;
        s.Set({{1,2,3,11},
               {4,5,6,12},
               {7,8,9,13}});

        Scheme target;
        target.Set({{7,8,9,13},
                    {4,5,6,12},
                    {1,2,3,11}});
        s.MirrorX();
        CHECK(s.data == target.data);
    }

SECTION("mirror y 3x3") {
        Scheme s;
        s.Set({{1,2,3},
               {4,5,6},
               {7,8,9}});

        Scheme target;
        target.Set({{3,2,1},
                    {6,5,4},
                    {9,8,7}});
        s.MirrorY();
        CHECK(s.data == target.data);
    }

SECTION("mirror y 3x4") {
        Scheme s;
        s.Set({{1,2,3,11},
               {4,5,6,12},
               {7,8,9,13}});

        Scheme target;
        target.Set({{11,3,2,1},
                    {12,6,5,4},
                    {13,9,8,7}});
        s.MirrorY();
        CHECK(s.data == target.data);
    }
}

#endif // SCHEME_TESTS_H
