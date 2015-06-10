#ifndef BLOCK_H_
#define BLOCK_H_
#include <vector>
#include <logic/agents/gamepart.h>

struct Block : GameBase
{
    Block *instantiate();

    Block(){}
    ~Block(){}
    Block(const Block&) = delete;
    Block& operator=(const Block&) = delete;
    std::string debugInfo();

private:
    Jtex m_tex = 0;
};

#endif // BLOCK_H_
