#ifndef TEX_GEN_H_
#define TEX_GEN_H_
#include "jtexture.h"
#include <vector>
#include "framebuffer.h"
#include "jargshader.h"
#include <memory>
#include <functional>

class TextureGenerator
{
public:
    TextureGenerator(void);
    ~TextureGenerator(void);
    void SetTextures(std::shared_ptr<Texture> tex);
    void SetResultTexture(std::shared_ptr<Texture> _tex);
    void SetShader(std::shared_ptr<JargShader> _shader);
    void RenderOnTempFbo(std::function<void()> func = [](){}) const;
    void SetParams(float tex);
    void Reset();
private:
    std::vector<std::shared_ptr<Texture>> texes;
    std::vector<float> params;
    std::shared_ptr<JargShader> shader;
    std::shared_ptr<Texture> target;
};

#endif

