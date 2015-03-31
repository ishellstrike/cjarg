#include "database.h"
#include "sge/prefecences.h"
#include "sge/fielsystem.h"
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include <logic/map/scheme.h>
#include "../agents/agents.hpp"

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
    if(static_cast<Jid>(item_db.size()) >= s)
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

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

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
        std::stringstream ss;
        std::string all;
        all.reserve(65536);
        while(!fs.eof())
        {
            std::string buf;
            fs >> buf;
            ss << buf;
        }
        fs.close();
        all = ss.str();

        LOG(info) << "parse " << file;
        rapidjson::Document d;
         d.Parse<0>(all.c_str());
        if(d.HasParseError())
        {
            LOG(error) << d.GetParseError();
            LOG(error) << all.substr(max(d.GetErrorOffset() - 20, 0), min(all.length(), 40));
            LOG(error) << "                    ^";
        }

        int loaded = 0;
        if(d.IsArray())
        {
            for(decltype(d.Size()) i=0; i < d.Size(); i++)
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

                    PARTS_PARSER

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

                    PARTS_PARSER

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

                    PARTS_PARSER

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
