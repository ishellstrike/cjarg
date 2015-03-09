#include "scheme.h"


void Scheme::MirrorX()
{
    for (int i = 0; i < size.x; ++i)
        for (int j = 0; j < size.y / 2; ++j)
            std::swap(data[i][j], data[i][static_cast<size_t>(size.y) - j - 1]);
}

void Scheme::MirrorY()
{
    for (int i = 0; i < size.x / 2; ++i)
        for (int j = 0; j < size.y; ++j)
            std::swap(data[i][j], data[static_cast<size_t>(size.x) - i - 1][j]);
}

void Scheme::RotateCCW()
{
    for (int i = 0; i < size.x; ++i)
        for (int j = i; j < size.y; ++j)
            std::swap(data[static_cast<size_t>(size.y) - j - 1][i], data[i][j]);
}

void Scheme::Transpose()
{
    for (int i = 0; i < size.x; ++i)
        for (int j = i; j < size.y; ++j)
            std::swap(data[j][i], data[i][j]);
}

void Scheme::Resize(glm::vec2 __size)
{
    data.clear();
    data.resize(static_cast<size_t>(size.x));
    for(auto &row : data)
        row.resize(static_cast<size_t>(size.y));
    size = __size;
}

void Scheme::LogData() const
{
    for (int j = 0; j < size.y; ++j)
    {
        std::string s;
        for (int i = 0; i < size.x; ++i)
        {
            s += data[i][j];
        }
        LOG(info) << s;
    }
}

void Scheme::Set(std::vector<std::vector<Letter>> __data)
{
    assert(data.size() == 0 && "empty matrix");
    data.clear();
    size = {__data.size(), __data[0].size()};
    data = __data;
}

void Scheme::NumericTransform(int __num)
{
    auto a = __num % TRANSFORM_AFTER_LAST;
    switch (a)
    {
        case TRANSFORM_MX:
        MirrorX();
        break;
        case TRANSFORM_MY:
        MirrorY();
        break;
        case TRANSFORM_RCW:
        RotateCCW();
        break;
    }
}
