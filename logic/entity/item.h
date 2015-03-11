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
        auto tex_id = val["id"].GetString();
        //id = database::instance()->item_db[database::instance()->item_pointer[tex_id]]->id;
        count = val["count"].GetInt();
    }
};

#endif // ITEM_H
