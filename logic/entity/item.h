#ifndef ITEM_H
#define ITEM_H
#include "rapidjson/document.h"
#include "../agents/gamepart.h"

struct Item : public GameBase
{
    int count = 1;

    Item(){}
    ~Item(){}
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;

    std::string description();
    std::string name();
    std::string fullInfo();
    std::string debugInfo();

    void deserialize(rapidjson::Value &val)
    {
        //auto tex_id = val["id"].GetString();
        //id = database::instance()->item_db[database::instance()->item_pointer[tex_id]]->id;
        count = val["count"].GetInt();
    }
};

#endif // ITEM_H
