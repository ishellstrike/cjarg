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

    //gen_helper::PlaceWall(s, {0,0,0}, {5,5,5}, 5, "glass");
    Scheme a = database::instance()->scheme_db.begin()->second[0];
    for(int i = 0; i < 5; i++) {
        a.NumericTransform(Noise::normalized_simplexnoise(ii,jj)*12345);
    }
    s->placeScheme(a, {1,1,1});
}
