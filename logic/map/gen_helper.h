#ifndef GEN_HELPER_H
#define GEN_HELPER_H
#include <memory>
#include "sector.h"

struct gen_helper
{
    /*!
     * \brief PlaceWall
     * \param s[out]
     * \param start
     * \param end
     * \param height
     */
   static void PlaceWall(std::shared_ptr<Sector> &s, const glm::vec3 &start, const glm::vec3 &end, float height, std::string id);

   static void PlaceRegion(std::shared_ptr<Sector> &s, const glm::vec3 &start, const glm::vec3 &end, std::string id);
};

#endif // GEN_HELPER_H
