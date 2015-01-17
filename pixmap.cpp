#include "pixmap.h"
#include "lodepng/lodepng.h"
#include "logger.h"
#include "jhelper.inl"

Pixmap::Pixmap(const std::string &a)
{
    auto error = lodepng::decode(data, width, height, a);
    if(error) LOG(info) << "png error " << error << ": " << lodepng_error_text(error) << " for " << a;
}

Pixmap::Pixmap(glm::vec2 size)
{
    width = size.x;
    height = size.y;
    data.resize(size.x * size.y * 4, 0);
}

Pixmap::~Pixmap()
{

}

void Pixmap::Blit(const Pixmap &source, const glm::vec2 &pos)
{
    assert(pos.x >= 0 && pos.y >= 0);
    if(width <= source.width + pos.x || height <= source.height + pos.y) {
        LOG(error) << "Blit error. Target image not enough large. " <<
                      string_format("(%g, %g) to (%g, %g) into (%d, %d)",
                                    pos.x, pos.y,
                                    source.width + pos.x, source.height + pos.y,
                                    width, height);
        throw std::out_of_range("target pixmap not enough large");
    }

    for(int i = 0; i < source.height; i++)
        memcpy(&data[(height * (i + pos.y) + pos.x)*4],
               &source.data[(source.height * i)*4],
               sizeof(unsigned char) * 4 * source.width);
}

