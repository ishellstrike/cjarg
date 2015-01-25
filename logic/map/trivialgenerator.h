#ifndef TRIVIALGENERATOR
#define TRIVIALGENERATOR
#include "sector.h"

struct Generator
{

};

struct TrivialGenerator : public Generator
{
    // LevelGenetarorStrategy interface
public:
    static void Generate(Sector &s);
};

#endif // TRIVIALGENERATOR

