#include "gen_helper.h"
#include "sge/helper.h"
#include "logic/base/database.h"


void gen_helper::PlaceWall(std::shared_ptr<Sector> &s, const glm::vec3 &start, const glm::vec3 &end, float height, std::string id)
{
    std::vector<glm::vec3> points;
    Bresencham3D(start, end, points);
    for(glm::vec3 &point : points)
    {
        for(int i = 0; i < height && i + point.z < RZ; i++)
        {
            s->block(point + glm::vec3(0,0,i), database::instantiateBlock(id));
        }
    }
}

void gen_helper::PlaceRegion(std::shared_ptr<Sector> &s, const glm::vec3 &start, const glm::vec3 &end, std::string id)
{
        for(int i = start.x; i <= end.x && i < RX; i++)
            for(int j = start.y; j <= end.y && j < RY; j++)
                for(int k = start.z; k <= end.z && k < RZ; k++)
                    s->block({i,j,k}, database::instantiateBlock(id));
}
