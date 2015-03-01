#ifndef ITEM_H
#define ITEM_H
#include "cereal/cereal.hpp"

class Item
{
public:
    Item();
    ~Item();

    int id = 0;
    int count = 1;

    template<class Archive>
    void save(Archive &ar) const
    {
        ar(CEREAL_NVP(id), CEREAL_NVP(count));
    }
};

#endif // ITEM_H
