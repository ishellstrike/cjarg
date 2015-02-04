#include "trivialgenerator.h"
#include "diamondsquare.h"
#include <glm/glm.hpp>
#include "sge/ClassicNoise.h"

void TrivialGenerator::Generate(Sector &s)
{
    //DiamondSquare ds;
    //Array2D<float> *a = ds.DsGenerate(RX, RY, 1);

    FORij
    {
        int ii = i + s.offset.x * RX;
        int jj = j + s.offset.y * RY;
        float c = (((
                     simplexnoise(ii/32.f,jj/32.f) +
                     simplexnoise(ii/16.f,jj/16.f)/2.f +
                     simplexnoise(ii/8.f,jj/8.f)/4.f)) * (float)RZ) + 5;

        c = glm::max((char)c, (char)0);
        c = glm::min((char)c, char(RZ - 2));
        s.ground[i][j] = c;

        for(int k=c; k>=0; k--)
            s.blocks[i][j][k]->id(1);
    }
}
