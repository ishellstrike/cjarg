#ifndef POINT_H
#define POINT_H
#include "point.h"

#include <glm/glm.hpp>
#include <unordered_map>

class Point
{
public:
    Point();
    Point(const glm::vec2 &p);

    template<typename T>
    Point(T x_, T y_) :
        x(x_),
        y(y_)
    {}

    ~Point();

    int x,y;

    bool operator==(const Point &other) const
      { return (x == other.x
                && y == other.y);
      }

    Point &operator=(const Point &other)
    {
        if(this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

class Point3
{
public:
    Point3();
    Point3(const glm::vec3 &p);

    template<typename T>
    Point3(T x_, T y_, T z_) :
        x(x_),
        y(y_),
        z(z_)
    {}

    ~Point3();

    int x,y,z;

    bool operator==(const Point3 &other) const
      { return (x == other.x
                && y == other.y
                && z == other.z);
      }

    Point3 &operator=(const Point3 &other)
    {
        if(this != &other)
        {
            x = other.x;
            y = other.y;
            z = other.x;
        }
        return *this;
    }
};

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {

  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& k) const
    {
      size_t seed = 0;
      hash_combine(seed, k.x);
      hash_combine(seed, k.y);
      return seed;
    }
  };

}

#endif // POINT_H
