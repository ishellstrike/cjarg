#ifndef ITEM_H
#define ITEM_H
#include "rapidjson/document.h"

class Item
{
public:
    Item();
    ~Item();

    int id = 0;
    int count = 1;

    void deserialize(rapidjson::Value &val)
    {
        id = val["id"].GetInt();
        count = val["count"].GetInt();
    }
};

#endif // ITEM_H
