#ifndef WISHLIST_H
#define WISHLIST_H
#include <vector>
#include <memory>
#include "../order.h"

struct Wish{
    std::shared_ptr<Order> linked = nullptr;
};

struct WishList
{
    std::vector<Wish> wishes;
    int wishCount();
    void addWish(Wish w);
};

#endif // WISHLIST_H
