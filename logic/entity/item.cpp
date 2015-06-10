#include "item.h"
#include "../base/database.h"
#include <sstream>

std::string Item::description()
{
    return database::instance()->getItem(id())->description;
}

std::string Item::name()
{
    return database::instance()->getItem(id())->name;
}

std::string Item::fullInfo()
{
    return "";
}

std::string Item::debugInfo()
{
    std::stringstream s;

    s << database::instance()->getItem(id())->debugInfo();

    return s.str();
}
