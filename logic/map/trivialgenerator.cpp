#include "trivialgenerator.h"
#include "diamondsquare.h"
#include <glm/glm.hpp>

void TrivialGenerator::Generate(Sector &s)
{
    DiamondSquare ds;
    Array2D<float> *a = ds.DsGenerate(RX, RY, 10);

    FORij
    {
        float c = ((((*a)[i][j])) * (float)RZ);
        c = glm::max((char)c, (char)0);
        c = glm::min((char)c, char(RZ - 2));
        s.ground[i][j] = c;

        for(int k=c; k>=0; k--)
            s.blocks[i][j][k]->id(1);
    }

    delete a;
}
