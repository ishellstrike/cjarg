#ifndef BLOCK_H_
#define BLOCK_H_
#include <vector>
#include <logic/agents/gamepart.h>

struct Block : GameBase
{
    std::shared_ptr<Block> instantiate();

    Block(){}
    ~Block(){}
    Block(const Block&) = delete;
    Block& operator=(const Block&) = delete;
    std::string debugInfo();
};

#endif // BLOCK_H_
