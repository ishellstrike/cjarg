#ifndef FRAME_BUF_H
#define FRAME_BUF_H
#include <GL/glew.h>
#include "jtexture.h"
class FrameBuffer
{
public:
    FrameBuffer(bool _depth = false);
    ~FrameBuffer();
    void bindTexture(const Texture& tex, GLuint attach = GL_COLOR_ATTACHMENT0);
    GLuint FBO;
    bool depth;
};
#endif

