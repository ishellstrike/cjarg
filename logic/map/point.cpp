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



Point3::Point3() :
    x(),
    y(),
    z()
{

}

Point3::Point3(const glm::vec3 &p) :
    x(p.x),
    y(p.y),
    z(p.z)
{

}

Point3::~Point3()
{

}
