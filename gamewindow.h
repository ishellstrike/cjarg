#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>
#include "logger.h"
#include "jargshader.h"
#include "spritebatch.h"
#include "framebuffer.h"
#include "ui_wins.h"
#include "fpscounter.h"
#include "gametimer.h"
#include "textureatlas.h"
#include "logic/map/sector.h"

class GameWindow {
public:
    bool Init();
    bool Destroy();
    bool Load();
    bool Unload();

    void Update();
    void Draw();

    void Mainloop();
    GameTimer gt;
    FPSCounter fps;

    static void Resize(int w, int h);

    GLFWmonitor *monitor = nullptr;
    GLFWwindow *window = nullptr;
    TextureAtlas atlas;
    Sector sec;

    glm::mat4 view, proj, model;
    static GameWindow *wi;
    std::shared_ptr<FrameBuffer> fb;
    std::shared_ptr<Texture> tex;

    GameWindow();
    ~GameWindow();

    std::shared_ptr<WinS> ws;

    std::shared_ptr<JargShader> basic, font;
    std::shared_ptr<SpriteBatch> batch;
};

#endif // GAMEWINDOW_H
