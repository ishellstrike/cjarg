#include "scheme.h"
#include "../base/parse_helper.h"

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

bool Scheme::deserialize(rapidjson::Value &__val)
{
    Scheme &s = *this;
    if(!__val.HasMember("building"))
    {
        LOG(error) << "scheme has no \"building\"";
        return false;

    }
    s.type = __val["building"].GetString();

    if(!__val.HasMember("dictionary"))
    {
        LOG(error) << "scheme has no \"dictionary\"";
        return false;
    }
    rapidjson::Value &dict = __val["dictionary"];
    if(dict.IsArray())
    {
        for(int j=0; j < dict.Size(); j++)
        {
            rapidjson::Value &pair = dict[j];
            s.dict[pair.Begin()->GetString()[0]] = (pair.Begin() + 1)->GetString();
        }
    }
        else
    {
        LOG(error) << "scheme has broken \"dictionary\" (must be [[\"i\",\"id_string\"], ...])";
        return false;
    }

    if(!__val.HasMember("size"))
    {
        LOG(error) << "scheme has no \"size\"";
        return false;
    }
    rapidjson::Value &size = __val["size"];
    if(!vec2ParseHelper(size, s.size))
    {
        LOG(error) << "scheme has broken \"size\" (must be [x,y])";
        return false;
    }
    s.Resize(s.size);

    if(!__val.HasMember("data"))
    {
        LOG(error) << "scheme has no \"data\"";
        return false;
    }
    rapidjson::Value &data = __val["data"];
    if(data.IsArray())
    {
        if(data.Size() != s.size.y)
        {
            LOG(error) << "scheme has broken \"data\", height is " <<
                          data.Size() << ", scheme has height " << s.size.y;
            return false;
        }
        for(int j=0; j < data.Size(); j++)
        {
            auto str = data[j].GetString();
            if(data[j].GetStringLength() != s.size.x)
            {
                LOG(error) << "scheme has broken \"data\", line " << j <<
                              " lenght is " << data[j].GetStringLength() << ", scheme has lenght " << s.size.x;
                return false;
            }
            for(int k = 0; k < data[j].GetStringLength(); ++k)
            {
                s.data[k][j] = str[k];
            }
        }
    }
    else
    {
        LOG(error) << "scheme has broken \"data\" (must be [\"   abcd   \", ...])";
        return false;
    }

    //test
    bool broken = false;
    for(int m = 0; m < s.size.x && !broken; m++)
        for(int n = 0; n < s.size.y && !broken; n++){
            if(s.data[m][n] == '.') continue;
            auto it = s.dict.find(s.data[m][n]);
            if(it == s.dict.end())
            {
                broken = true;
                LOG(error) << "\"" << s.data[m][n] << "\" not found in dictionary";
            }
        }
    if(broken) {
        return false;
    }
    return true;
}
