#include "database.h"
#include "sge/prefecences.h"
#include "sge/fielsystem.h"
#include <fstream>
#include "rapidjson/document.h"
#include <logic/map/scheme.h>
#include "../agents/agents.hpp"

#define CASTERS_PART                                                                                               \
    if(val.HasMember("parts")) {                                                                                   \
        rapidjson::Value &arr = val["parts"];                                                                      \
        if(val["parts"].IsArray())                                                                                 \
        for(int a = 0; a < arr.Size(); a++)                                                                        \
        {                                                                                                          \
            rapidjson::Value &part = arr[a];                                                                       \
            if(part.HasMember("type")) {                                                                           \
                CASTERS                                                                                            \
                /*else here*/ LOG(error) << "record \"" << id << "\" agent #" << a + 1 << " has unknown \"type\""; \
            }                                                                                                      \
            else                                                                                                   \
                LOG(error) << "record \"" << id << "\" agent #" << a + 1 << " has no type";                        \
        }                                                                                                          \
        else                                                                                                       \
            LOG(error) << "record \"" << id << "\" parts is not valid agents array";                               \
    }

void database::registerBlock(const std::string &s, StaticBlock *b)
{
    if(block_pointer.find(s) != block_pointer.end())
        LOG(info) << "block " << s << " redefinition";
    block_db.push_back(std::unique_ptr<StaticBlock>(b));
    block_back_pointer[block_db.size() - 1] = s;
    block_pointer[s] = block_db.size() - 1;

    b->id = block_db.size() - 1;
    //b->full_id = s;
    //LOG(info) << "register \"" << s << "\" as " << block_db.size() - 1;
}

void database::registerItem(const std::string &s, StaticItem *i)
{
    if(item_pointer.find(s) != item_pointer.end())
        LOG(info) << "item " << s << " redefinition";
    item_db.push_back(std::unique_ptr<StaticItem>(i));
    item_back_pointer[item_db.size() - 1] = s;
    item_pointer[s] = item_db.size() - 1;

    i->id = item_db.size() - 1;
    //i->full_id = s;
    //LOG(info) << "register \"" << s << "\" as " << block_db.size() - 1;
}

StaticItem *database::getItem(const std::string &s)
{
    if(item_pointer.find(s) == item_pointer.end())
        return item_db[0].get();
    return item_db[item_pointer[s]].get();
}

StaticItem *database::getItem(const Jid &s)
{
    if(item_db.size() >= s)
        return item_db[0].get();
    return item_db[s].get();
}

void database::registerCreature(const std::string &s, StaticCreature *i)
{
    if(creature_pointer.find(s) != creature_pointer.end())
        LOG(info) << "creature " << s << " redefinition";
    creature_db.push_back(std::unique_ptr<StaticCreature>(i));
    creature_back_pointer[creature_db.size() - 1] = s;
    creature_pointer[s] = creature_db.size() - 1;

    i->id = creature_db.size() - 1;
}

StaticCreature *database::getCreature(const std::string &s)
{
    if(creature_pointer.find(s) == creature_pointer.end())
        return creature_db[0].get();
    return creature_db[creature_pointer[s]].get();
}

void database::Load()
{
    StaticBlock *ss = new StaticBlock();
    ss->setTexture(0);
    ss->transparent = true;
    registerBlock("air", ss);

    ss = new StaticBlock();
    ss->setTexture("error.png");
    registerBlock("error", ss);

    StaticCreature *sc = new StaticCreature;
    registerCreature("error", sc);

    std::vector<std::string> files;
    getFiles(Prefecences::Instance()->getJsonDir(), files);

    for(std::string file : files)
    {
        std::ifstream fs(Prefecences::Instance()->getJsonDir() + file);
        std::string all;
        all.reserve(65536);
        while(!fs.eof())
        {
            std::string buf;
            fs >> buf;
            all += buf;
        }
        fs.close();

        LOG(info) << "parse " << file;
        rapidjson::Document d;
         d.Parse<0>(all.c_str());
        if(d.HasParseError())
        {
            LOG(error) << d.GetParseError();
            LOG(error) << all.substr(max(d.GetErrorOffset() - 20, (size_t)0), min(all.length(), (size_t)40));
            LOG(error) << "                    ^";
        }

        int loaded = 0;
        if(d.IsArray())
        {
            for(int i=0; i < d.Size(); i++)
            {
                rapidjson::Value &val = d[i];
                if(!val.HasMember("type"))
                {
                    LOG(error) << "record #" << i+1 << " from " << file << " has no \"type\"";
                    continue;
                }
                std::string type = val["type"].GetString();

                // === parse part ===
                if(type == "block")
                {
                    if(!val.HasMember("id"))
                    {
                        LOG(error) << "record #" << i+1 << " from " << file << " has no \"id\"";
                        continue;
                    }

                    StaticBlock *b = new StaticBlock();
                    b->etalon = std::unique_ptr<Block>(new Block());
                    b->etalon->parts = std::unique_ptr<Dynamic>(new Dynamic());

                    std::string id = val["id"].GetString();

                    b->deserialize(val);

                    if(val.HasMember("alltex") || val.HasMember("tex")) {
                        if(val.HasMember("alltex")) b->setTexture(val["alltex"].Begin()->GetString());
                        else
                        if(val.HasMember("tex")) {
                            rapidjson::Value &arr = val["tex"];
                            for(int a = 0; a < arr.Size(); a++)
                                b->setTexture(static_cast<StaticBlock::SIDE>(a), arr[a].Begin()->GetString());
                        } else
                            LOG(error) << "block " << id << " from " << file << " has no \"tex\" | \"alltex\"";
                    }

                    CASTERS_PART

                    if(b->etalon->parts->isEmpty())
                    {
                        b->etalon->parts = nullptr;
                    }

                    registerBlock(id, b);
                    loaded ++;
                }

                if(type == "item")
                {
                    if(!val.HasMember("id"))
                    {
                        LOG(error) << "record #" << i+1 << " from " << file << " has no \"id\"";
                        continue;
                    }

                    StaticItem *b = new StaticItem;
                    b->etalon = std::unique_ptr<Item>(new Item());
                    b->etalon->parts = std::unique_ptr<Dynamic>(new Dynamic());

                    std::string id = val["id"].GetString();
                    b->full_id = id;

                    b->deserialize(val);

                    CASTERS_PART

                    if(b->etalon->parts->isEmpty())
                    {
                        b->etalon->parts = nullptr;
                    }

                    registerItem(id, b);
                    loaded ++;
                }

                if(type == "creature")
                {
                    if(!val.HasMember("id"))
                    {
                        LOG(error) << "record #" << i+1 << " from " << file << " has no \"id\"";
                        continue;
                    }

                    StaticCreature *b = new StaticCreature;
                    b->etalon = std::unique_ptr<Creature>(new Creature());
                    b->etalon->parts = std::unique_ptr<Dynamic>(new Dynamic());
                    b->etalon->subparts = std::unique_ptr<CreaturePart>(new CreaturePart);

                    std::string id = val["id"].GetString();
                    b->full_id = id;

                    b->deserialize(val);

                    CASTERS_PART

                    if(val.HasMember("creaturepart") || val["creaturepart"].IsArray()) {
                        rapidjson::Value &d = val["creaturepart"];
                        b->etalon->subparts->deserialize(*d.Begin());
                    }

                    if(b->etalon->parts->isEmpty())
                    {
                        b->etalon->parts = nullptr;
                    }

                    registerCreature(id, b);
                    loaded ++;
                }

                if(type == "scheme")
                {
                    Scheme s;
                    if(!s.deserialize(val))
                    {
                        LOG(error) << "record #" << i+1 << " from " << file << " broken, skipped";
                        continue;
                    }

                    scheme_db[s.type].push_back(s);
                }
            }
        } else
            LOG(error) << "not valid object array";
        LOG(info) << loaded << " loaded";
        LOG(info) << "---";
    }
}

database::database()
{

}

database::~database()
{
}

database *database::m_inst = nullptr;
