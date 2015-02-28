#include "database.h"
#include "sge/prefecences.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "sge/fielsystem.h"
#include <fstream>

void database::registerBlock(std::string s, StaticBlock *b)
{
    block_db.push_back(std::unique_ptr<StaticBlock>(b));
    block_back_pointer[block_db.size() - 1] = s;
    block_pointer[s] = block_db.size() - 1;
    //LOG(info) << "register \"" << s << "\" as " << block_db.size() - 1;
}

void database::registerItem(std::string s, Item *i)
{
    item_db.push_back(i);
    item_pointer[s] = item_db.size() - 1;
    //LOG(info) << "register \"" << s << "\" as " << block_db.size() - 1;
}

void database::Load()
{
    std::vector<std::string> files;
    getFiles(Prefecences::Instance()->getJsonDir(), files);

    for(std::string file : files)
    {
        std::ifstream fs(Prefecences::Instance()->getJsonDir() + file);
        std::string buf;
        std::string all;
        all.reserve(65536);
        while(!fs.eof())
        {
            fs >> buf;
            all += buf;
        }

        LOG(info) << "parse " << file;
        rapidjson::Document d;
         d.Parse<0>(all.c_str());
        if(d.HasParseError())
        {
            LOG(error) << d.GetParseError();
        }

        int loaded = 0;
        if(d.IsArray())
        {
            for(int i=0; i < d.Size(); i++)
            {
                rapidjson::Value &val = d[i];
                if(!val.HasMember("type"))
                {
                    LOG(error) << "record #" << i+1 << " from " << file << " has no type";
                    continue;
                }
                std::string type = val["type"].GetString();

                if(!val.HasMember("id"))
                {
                    LOG(error) << "record #" << i+1 << " from " << file << " has no id";
                    continue;
                }

                if(type == "block")
                {
                    LOG(info) << "block " << val["id"].GetString();
                    loaded ++;
                }

                if(type == "item")
                {
                    LOG(info) << "item " << val["id"].GetString();
                    loaded ++;
                }
            }
        } else
            LOG(error) << "not valid object array";
        LOG(info) << loaded << " loaded";
        LOG(info) << "---";
    }

    cereal::JSONInputArchive arch();
}

database::database()
{

}

database::~database()
{
    for(Item *item: item_db){
        delete item;
    }
}

database *database::m_inst = nullptr;
