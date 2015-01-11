#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "jtexture.h"
#include <string>
#include <memory>
#include "jargShader.h"

#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/config/ftheader.h>

#define SIZE 10000
class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch();

    glm::vec3 *pos = nullptr;
    glm::vec2 *uv = nullptr;
    glm::vec4 *col = nullptr;

    GLuint *index = nullptr;
    unsigned int cur = 0;

    GLuint current = 0;
    GLuint m_vbo[4];

    std::shared_ptr<Texture> font;
    std::shared_ptr<Texture> fontatlas;

    glm::mat4 uniform;

    std::shared_ptr<JargShader> font_program, basic_program, color_program, current_program;

    void initFreeType();
    void setUniform(glm::mat4 &uni);

    glm::vec2 renderText(const char *text, float x, float y, float sx, float sy, glm::vec4 &col_);

    void render();
    void drawRect(const glm::vec2 &loc, const glm::vec2 &size, const glm::vec4 &_col);
    glm::vec2 renderAtlas();
    void drawQuad(const glm::vec2 &loc, const glm::vec2 &size, const Texture &tex, const glm::vec4 &col_);
    void drawLine(const glm::vec2 &start, const glm::vec2 &end, float width, const glm::vec4 &color);
private:
    FT_Face m_ftFace;
    void drawQuadText(glm::vec2 &loc, glm::vec2 &size, const Texture &tex, glm::vec4 &color);
    //glm::vec2 renderText(const char *text, float x, float y, float sx, float sy, glm::vec4 &color);
};
#endif // SPRITEBATCH_H
