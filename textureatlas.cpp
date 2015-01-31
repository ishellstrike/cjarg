#include "textureatlas.h"
#include "fielsystem.h"
#include "pixmap.h"

TextureAtlas::TextureAtlas()
{

}

TextureAtlas::~TextureAtlas()
{

}

void TextureAtlas::LoadAll(const std::string &a)
{
    std::vector<std::string> files;
    getFiles("data/textures/", files);
    LOG(info) << "texatlas found " << files.size() << " files";

    Pixmap atlas(glm::vec2(2048, 2048));

    int x = 0, y = 0, i = 0;
    for(std::string file: files)
    {
        Pixmap tex("data/textures/"+file);
        atlas.Blit(tex, glm::vec2(x * 32, y * 32));
        x++;
        if(x + 1 >= 2048/32)
        {
            x = 0;
            y++;
        }
        i++;
    }
    LOG(info) << "texatlas load " << i << " pixmaps";
    tex.Load(atlas, false, true);
    LOG(info) << "texatlas load texture";
}


Texture TextureAtlas::tex;
