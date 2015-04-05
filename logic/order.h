#ifndef ORDER_H
#define ORDER_H
#include <glm/glm.hpp>
#include <list>
#include <memory>

struct Order
{
    enum Type {
        Dig,
        Build,
        Error,
        Done
    };

    Type type = Error;
    glm::vec3 pos;
    //Priority priority = normal;

    Order(){}
    Order(Type t, glm::vec3 p) : type(t), pos(p){}
    ~Order(){}
    Order(const Order&) = delete;
    Order& operator=(const Order&) = delete;
    void markDone();
};

struct OrderList {
    typedef std::list<
                            std::shared_ptr<Order>
                       > Olist;

    Olist in_progress;
    Olist active;
    Olist diabled;
    Olist::iterator cur;
};

#endif // ORDER_H
