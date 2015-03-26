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
            std::unique_ptr<Item> item = std::unique_ptr<Item>(new Item);
            item->deserialize(_item);

            items.push_back(std::move(item));
        }
    }

    LOG(verbose) << "chest with items " << items.size();
}

void Chest::Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l)
{

}

void Chest::Init(const glm::vec3 &pos, const Level &l)
{

}

