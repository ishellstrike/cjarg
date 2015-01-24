#include "level.h"
#include "textureatlas.h"
#include "colorextender.h"

Level::Level(LevelWorker &lw)
{
    active[Point(1,1)] = lw.getSector({1,1});
}

Level::~Level()
{

}

void Level::Draw(SpriteBatch &sb)
{
    for(SectorMapPair pair: active)
    {
        //if(pair.first)
        {
            FORijk
            {

                sb.drawQuadAtlas({i*32.f, j*32.f}, {32.f, 32.f}, TextureAtlas::tex, pair.second->blocks[i][j][0]->id(), WHITE);
            }
        }
    }
}

