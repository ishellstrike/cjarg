#ifndef MEMLIST_H
#define MEMLIST_H
#include <string>
#include <vector>

struct Mem{
    Mem(){}
    Mem(std::string s, int m = 0) : info(s), modifer(m) {}
    std::string info = "";
    int modifer = 0;
};

struct MemList
{
    void addMem(const Mem &m);
    std::vector<std::string> getMemList();
    int getEffcet();

private:
    std::vector<Mem> mem = std::vector<Mem>(20);
    short last = 0;
};

#endif // MEMLIST_H
