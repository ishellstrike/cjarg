#include "trivialgenerator.h"
#include "diamondsquare.h"
#include <glm/glm.hpp>
#include "sge/ClassicNoise.h"
#include <thread>
#include "logic/base/database.h"
#include "sge/textureatlas.h"
#include "gen_helper.h"

void TrivialGenerator::Generate(std::shared_ptr<Sector> s)
{
    //DiamondSquare ds;
    //Array2D<float> *a = ds.DsGenerate(RX, RY, 1);

     FORij
     {
         int ii = i + s->offset.x * RX;
         int jj = j + s->offset.y * RY;
         float c = (((Noise::simplexnoise(ii/64.f,jj/64.f)/2.f +
                     (Noise::simplexnoise(ii/32.f,jj/32.f) +
                      Noise::simplexnoise(ii/8.f,jj/8.f) +
                      Noise::simplexnoise(ii/16.f,jj/16.f) +
                      Noise::simplexnoise(ii/64.f,jj/64.f)*3)/7.f)) * (float)RZ);

         c = glm::max(c, 0.f);
         c = glm::min(c, RZ - 2.f);

         s->blocks[i][j][(int)c] = std::unique_ptr<Block>(database::instance()->getStaticBlock("grass")->etalon->instantiate());
         for(int k=c - 1; k>=0; k--)
             s->blocks[i][j][k] = std::unique_ptr<Block>(database::instance()->getStaticBlock("dirt")->etalon->instantiate());
     }
}


void TestGenerator_City1::Generate(std::shared_ptr<Sector> s)
{
    int ii = s->offset.x * RX;
    int jj = s->offset.y * RY;
    FORij
    {

        if(Noise::normalized_simplexnoise((i + ii)/32.f,(j + jj)/32.f) +
           Noise::normalized_simplexnoise((i + ii)/64.f,(j + jj)/64.f) > 1.f)
            s->blocks[i][j][0] = std::unique_ptr<Block>(database::instance()->getStaticBlock("grass")->etalon->instantiate());
        else
            s->blocks[i][j][0] = std::unique_ptr<Block>(database::instance()->getStaticBlock("dirt")->etalon->instantiate());
    }

    //gen_helper::PlaceWall(s, {0,0,0}, {5,5,5}, 5, "glass");
    Scheme a = database::instance()->scheme_db.begin()->second[0];
    for(int i = 0; i < 5; i++) {
        a.NumericTransform(Noise::normalized_simplexnoise(ii,jj)*12345);
    }

    s->placeScheme(a, {1,1,1});
    gen_helper::PlaceRegion(s, {1,1,2}, {1 + a.size.x,1 + a.size.y, 2}, "bricks");
    s->placeScheme(a, {1,1,3});
    gen_helper::PlaceRegion(s, {1,1,4}, {1 + a.size.x,1 + a.size.y, 4}, "bricks");
    s->placeScheme(a, {1,1,5});
    gen_helper::PlaceRegion(s, {1,1,6}, {1 + a.size.x,1 + a.size.y, 6}, "bricks");
    s->placeScheme(a, {1,1,7});
}
