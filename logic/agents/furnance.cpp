#include "furnance.h"

Agent *Furnance::instantiate() const
{
    return nullptr;
}

void Furnance::deserialize(rapidjson::Value &val)
{
    if(val.HasMember("temp"))
    {
        temp = val["temp"].GetInt();
    }
}
