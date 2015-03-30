#ifndef ORDER_H
#define ORDER_H
#include <glm/glm.hpp>
#include <vector>
#include <memory>

struct Order
{
    enum Type {
        Dig,
        Error
    };

    Type type = Error;
    glm::vec3 pos;
    //Priority priority = normal;

    Order(){}
    ~Order(){}
    Order(const Order&) = delete;
    Order& operator=(const Order&) = delete;
};

struct OrderList {
    typedef std::vector<
                            std::shared_ptr<Order>
                       > Olist;

    Olist in_progress;
    Olist active;
    Olist diabled;
    Olist::iterator cur;
};

#endif // ORDER_H
