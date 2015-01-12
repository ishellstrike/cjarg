#ifndef LOGGER_H
#define LOGGER_H
#include <ostream>
#include <string.h>
#include <stdarg.h>
#include <memory>

enum {
    info,
    error,
    fatal
};

#define LOG(level) Log(level, __FILE__, __LINE__)

inline std::string string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2;
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]);
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

class Log
{
public:
    Log(int type, const char *file, int line);
    ~Log();

    int m_type;

    std::ostream o_stream;

    template<typename T>
    Log &operator <<(const T &a)
    {
        o_stream << a;

        return *this;
    }
};

#endif // LOGGER_H
