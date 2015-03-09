#include "parse_helper.h"
#include "sge/logger.h"

bool vec2ParseHelper(rapidjson::Value &__val, glm::vec2 &vec)
{
    if(!__val.IsArray() || __val.Size() != 2)
        return false;
    vec = {__val.Begin()->GetInt(), (__val.Begin() + 1)->GetInt()};
    return true;
}
