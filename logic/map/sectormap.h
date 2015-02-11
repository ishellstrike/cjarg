#ifndef SECTORMAP_H
#define SECTORMAP_H
#include <unordered_map>
#include "sector.h"
#include "point.h"
#include <memory>

typedef std::unordered_map<Point, std::shared_ptr<Sector>> SectorMap;
typedef std::pair<Point, std::shared_ptr<Sector>> SectorMapPair;

#endif // SECTORMAP_H
