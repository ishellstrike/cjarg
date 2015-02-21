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
    static void Generate(std::shared_ptr<Sector> s);
};

#endif // TRIVIALGENERATOR

