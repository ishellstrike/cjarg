#ifndef POINT_H
#define POINT_H
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

namespace std {

  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& k) const
    {
      return (hash<int>()(k.x)
               ^ (hash<int>()(k.y) << 1));
    }
  };

}

#endif // POINT_H
