#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <logic/agents/gamepart.h>
#include "../agents/agent.h"
#include "cereal/cereal.hpp"

class Block
{
public:
    Block();
    /*!
     * \brief Using for create database examples
     * \param a
     * \param agents_
     */
    Block(const std::vector<Agent *> &agents_, const std::string &id);
    ~Block();

    Jid id();

    void id(Jid id_);

    std::unique_ptr<Dynamic> parts = nullptr;

    Jid m_id = 0;
    Jtex m_tex = 0;

    template<class Archive>
    void save(Archive &ar) const
    {
        if(parts)
            ar(cereal::make_nvp("parts", *parts));
    }
};

#endif // BLOCK_H
