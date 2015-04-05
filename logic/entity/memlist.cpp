#include "memlist.h"
#include "sge/helper.h"

void MemList::addMem(const Mem &m)
{
    mem[last] = m;
    last ++;
    if(last >= mem.size())
        last = 0;
}

std::vector<std::string> MemList::getMemList()
{
    std::vector<std::string> s;
    for(size_t i = last; i < last + mem.size(); ++i)
    {
        size_t j = i % mem.size();
        s.push_back(string_format("%s (%d)", mem[j].info.c_str(), mem[j].modifer));
    }

    return s;
}

int MemList::getEffcet()
{
    int e = 0;
    for(Mem &m : mem)
        e += m.modifer;

    return e;
}
