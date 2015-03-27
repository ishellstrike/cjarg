#ifndef SKILLLIST_H
#define SKILLLIST_H
#include <string>

struct Skill {
    virtual std::string getName() = 0;
    virtual std::string getDescr() = 0;
    virtual std::string getStat() = 0;
    char level = 0;
};

struct Butcher : public Skill {
    std::string getName();
    std::string getDescr();
    std::string getStat();
};

struct Cooking : public Skill {
    std::string getName();
    std::string getDescr();
    std::string getStat();
    int cooked = 0;
    int cooked_master = 0;
    int failed = 0;
};

struct SkillList
{
public:
    std::string getFullList();

    Butcher butcher;
    Cooking cooking;
};

#endif // SKILLLIST_H
