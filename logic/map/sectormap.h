#ifndef SECTORMAP_H
#define SECTORMAP_H
#include <unordered_map>
#include "sector.h"
#include "point.h"

typedef std::unordered_map<Point, Sector*> SectorMap;

#endif // SECTORMAP_H
