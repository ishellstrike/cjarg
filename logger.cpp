#include "logger.h"
#include <iostream>
#include <ctime>
#include <memory>


Log::Log(int type, const char *file, int line) :
    o_stream(std::cout.rdbuf()),
    m_type(type)
{
    switch (m_type) {
    case info:
        o_stream << "I";
        break;
    case error:
        o_stream << "E";
        break;
    case fatal:
        o_stream << "F";
        break;
    default:
        o_stream << "?";
        break;
    }

    o_stream << " " << string_format("%06d", clock())
             << " " << file << " " << string_format("%3d", line) << " ";
}

Log::~Log()
{
    o_stream << std::endl;
}

