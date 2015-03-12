#include "chest.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "sge/logger.h"

Agent *Chest::instantiate() const
{
    Chest *chest = new Chest();
    return chest;
}

void Chest::deserialize(rapidjson::Value &val)
{
//    rapidjson::StringBuffer is;
//    rapidjson::PrettyWriter<rapidjson::StringBuffer> pw(is);
//    val.Accept(pw);
//    LOG(info) << is.GetString();

    if(val.HasMember("items"))
    {
        rapidjson::Value &_items = val["items"];
        for(int a = 0; a < _items.Size(); a++)
        {
            rapidjson::Value &_item = _items[a];
            Item item;
            item.deserialize(_item);

            items.push_back(item);
        }
    }
}

void Chest::Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l)
{

}

void Chest::Init(const glm::vec3 &pos, const Level &l)
{

}

