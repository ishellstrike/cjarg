#ifndef STATICITEM_H
#define STATICITEM_H
#include "item.h"
#include <memory>
#include <string>
#include <sstream>
#include "../agents/gamepart.h"
#include "rapidjson/document.h"

class StaticItem
{
public:
    StaticItem();
    ~StaticItem();
    StaticItem(const StaticItem&) = delete;
    StaticItem& operator=(const StaticItem&) = delete;

    std::unique_ptr<Item> etalon;
    std::string full_id;
    int id;

    //trivial vars
    std::string name = "";
    std::string description = "";
    int weight = 0;

    void deserialize(const rapidjson::Value &val)
    {
        DESERIALIZE(NVP(name),NVP(description),NVP(weight));
    }

    std::string debugInfo()
    {
        std::stringstream s;
        s << DEBUGINFO(name);
        s << DEBUGINFO(description);
        s << DEBUGINFO(weight);

        return s.str();
    }
};

#endif // STATICITEM_H
