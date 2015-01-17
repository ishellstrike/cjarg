#include "jsonparser.h"
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "logger.h"
#include "fielsystem.h"
#include <vector>

JsonParser::JsonParser()
{
}

void JsonParser::parseDataDirectory()
{
    std::vector<std::string> files;
    getFiles("data/json/", files);

    std::filebuf fb;
    if (fb.open ("data/json/error.json",std::ios::in))
    {
      std::istream is(&fb);

      Json::Value root;
      Json::Reader reader;
      bool parsingSuccessful = reader.parse( is, root );
      if ( !parsingSuccessful )
      {
          LOG(info)  << "Failed to parse\n" << reader.getFormatedErrorMessages();
      }
    }
}

/*
    std::filebuf fb;
    if (fb.open ("data/json/aaa.json",std::ios::in))
    {
      std::istream is(&fb);

      Json::Value root;
      Json::Reader reader;
      bool parsingSuccessful = reader.parse( is, root );
      if ( !parsingSuccessful )
      {
          LOG(info)  << "Failed to parse\n" << reader.getFormatedErrorMessages();
      }
    }

 */
