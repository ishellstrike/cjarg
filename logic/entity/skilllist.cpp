#include "skilllist.h"
#include "sge/helper.h"
#include <sstream>

static const char max_level = 4;
static const std::string levels[max_level] = {"начинающий", "опытный", "профессиональный", "мастер"};

#define FORSKILL(skill) { if(skill.level > 0) { ss << levels[skill.level - 1] << " " << skill.getName() << "\n"; } }

std::string SkillList::getFullList()
{
    std::stringstream ss;
    FORSKILL(butcher);
    FORSKILL(cooking);
    if(ss.str().length() == 0)
        ss << "не имеет никаких навыков";

    return ss.str();
}


std::string Butcher::getName()
{
    return "мясник";
}

std::string Butcher::getDescr()
{
    return "отвечает за разделку -- за количество и качество получаемых при разделке предметов";
}

std::string Butcher::getStat()
{
    return "";
}


std::string Cooking::getName()
{
    return "повар";
}

std::string Cooking::getDescr()
{
    return "";
}

std::string Cooking::getStat()
{
    std::stringstream s;
    s << "приготовлено блюд: " << cooked << "\n";
    s << "из них высшего качества: " << cooked_master << "\n";
    s << "испорчено: " << failed << "\n";

    return s.str();
}

#undef FORSKILL
