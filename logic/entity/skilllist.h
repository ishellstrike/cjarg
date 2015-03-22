#ifndef SKILLLIST_H
#define SKILLLIST_H
#include <string>

struct Skill {
    virtual std::string getName() = 0;
    virtual std::string getDescr() = 0;
    virtual std::string getStat() = 0;
    char level;
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
    int cooked;
    int cooked_master;
    int failed;
};

struct SkillList
{
public:
    std::string getFullList();

    Butcher butcher;
    Cooking cooking;
};

#endif // SKILLLIST_H
