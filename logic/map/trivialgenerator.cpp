#include "trivialgenerator.h"
#include "diamondsquare.h"
#include <glm/glm.hpp>
#include "sge/ClassicNoise.h"
#include <thread>
#include "logic/base/database.h"
#include "sge/textureatlas.h"

void TrivialGenerator::Generate(std::shared_ptr<Sector> s)
{
    //DiamondSquare ds;
    //Array2D<float> *a = ds.DsGenerate(RX, RY, 1);

     FORij
     {
         int ii = i + s->offset.x * RX;
         int jj = j + s->offset.y * RY;
         float c = (((simplexnoise(ii/64.f,jj/64.f)/2.f + (simplexnoise(ii/32.f,jj/32.f) + simplexnoise(ii/8.f,jj/8.f) + simplexnoise(ii/16.f,jj/16.f) + simplexnoise(ii/64.f,jj/64.f)*3)/7.f)) * (float)RZ);

         c = glm::max(c, 0.f);
         c = glm::min(c, RZ - 2.f);

         s->blocks[i][j][(int)c]->id(database::instance()->block_pointer["grass"]);
         for(int k=c - 1; k>=0; k--)
             s->blocks[i][j][k]->id(database::instance()->block_pointer["dirt"]);
     }
}


void TestGenerator_City1::Generate(std::shared_ptr<Sector> s)
{
    FORij
    {

        s->blocks[i][j][0]->id(database::instance()->block_pointer["dirt"]);
    }
    int ii = s->offset.x * RX;
    int jj = s->offset.y * RY;

    if (normalized_simplexnoise(ii, jj) > 0.2)
    {
        for(int i = static_cast<int>(normalized_simplexnoise(ii/16.f,jj/16.f) * 15); i > 0; i--)
        {
            glm::vec2 pos = glm::vec2(normalized_simplexnoise(ii/21.f + i, jj/22.f + i) * RX, normalized_simplexnoise(ii/11.f + i, jj/11.f + i) * RY);
            for(int k = 0; k < static_cast<int>(normalized_simplexnoise(ii/16.f + i, jj/16.f + i) * 20); k++)
                for(int n = 0; n < static_cast<int>(normalized_simplexnoise(ii/16.f + i, jj/16.f + i) * 20); n++)
                {
                    if(pos.x + k < RX - 1 && pos.y + n < RY - 1)
                    {
                        for(int z = static_cast<int>(normalized_simplexnoise(ii/26.f + i, jj/26.f + i) * 15); z > 0; z--)
                            s->blocks[static_cast<int>(pos.x) + k][static_cast<int>(pos.y) + n][z]->id(database::instance()->block_pointer["bricks"]);
                    }
                }
        }
    }
}
