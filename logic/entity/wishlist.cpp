#include "wishlist.h"




int WishList::wishCount()
{
    return wishes.size();
}

void WishList::addWish(Wish w)
{
    wishes.push_back(std::move(w));
}
