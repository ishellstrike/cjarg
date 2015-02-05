#include "trivialgenerator.h"
#include "diamondsquare.h"
#include <glm/glm.hpp>
#include "sge/ClassicNoise.h"
#include <thread>
#include "sge/textureatlas.h"

void TrivialGenerator::Generate(Sector &s)
{
    //DiamondSquare ds;
    //Array2D<float> *a = ds.DsGenerate(RX, RY, 1);

    FORij
    {
        int ii = i + s.offset.x * RX;
        int jj = j + s.offset.y * RY;
        float c = ((((simplexnoise(ii/32.f,jj/32.f) + simplexnoise(ii/8.f,jj/8.f) + simplexnoise(ii/16.f,jj/16.f) + simplexnoise(ii/64.f,jj/64.f)*3)/6.f)+1) * (float)RZ / 2.f);

        c = glm::max(c, 0.f);
        c = glm::min(c, RZ - 2.f);
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));

        for(int k=c; k>=0; k--)
            s.blocks[i][j][k]->id(TextureAtlas::refs["gravel.png"]);
    }
}
