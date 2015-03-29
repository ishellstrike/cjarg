#include "creaturepart.h"
#include "sge/logger.h"

void CreaturePart::deserialize(rapidjson::Value &val)
{
    id = val.HasMember("id") ? val["id"].GetString() : (LOG(error) << "creaturepart has no id", "error");
    count = val.HasMember("count") ? val["count"].GetInt() : 1;
    if(val.HasMember("creaturepart") && val["creaturepart"].IsArray())
    {
        rapidjson::Value &d = val["creaturepart"];
        for(int i = 0; i<d.Size(); i++)
        {
            std::unique_ptr<CreaturePart> c = std::unique_ptr<CreaturePart>(new CreaturePart);
            c->deserialize(d[i]);
            subparts.push_back(std::move(c));
        }
    }
}

CreaturePart *CreaturePart::instantiate() const
{
    CreaturePart *c = new CreaturePart();
    c->count = count;
    c->id = id;
    for(int i = 0; i < subparts.size(); i++)
    {
        if(subparts[i])
            c->subparts.push_back(std::unique_ptr<CreaturePart>(subparts[i]->instantiate()));
    }

    return c;
}
