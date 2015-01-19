#include "point.h"

Point::Point() :
    x(),
    y()
{
}

Point::Point(const glm::vec2 &p) :
    x(p.x),
    y(p.y)
{

}

Point::~Point()
{

}

