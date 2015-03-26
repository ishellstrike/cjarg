#ifndef ITEM_H
#define ITEM_H
#include "rapidjson/document.h"
#include "../agents/gamepart.h"

struct Item
{
    int id = 0;
    int count = 1;

    std::unique_ptr<Dynamic> parts = nullptr;

    Item(){}
    ~Item(){}
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;

    void deserialize(rapidjson::Value &val)
    {
        auto tex_id = val["id"].GetString();
        //id = database::instance()->item_db[database::instance()->item_pointer[tex_id]]->id;
        count = val["count"].GetInt();
    }
};

#endif // ITEM_H
