#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>
#include "logger.h"
#include "jargShader.h"
#include "spritebatch.h"
#include "FrameBuffer.h"
#include "WinS.h"

class GameWindow {
public:
    bool Init();
    bool Destroy();
    bool Load();
    bool Unload();

    void Update();
    void Draw();

    void Mainloop();

    static void Resize(int w, int h);

    GLFWmonitor *monitor;
    GLFWwindow *window;

    glm::mat4 view, proj, model;
    static GameWindow *wi;
    std::shared_ptr<FrameBuffer> fb;
    std::shared_ptr<Texture> tex;

    GameWindow();
    ~GameWindow();

    WinS ws;

    std::shared_ptr<JargShader> basic, font;
    std::shared_ptr<SpriteBatch> batch;

private:
    GLFWwindow *m_window;
};

#endif // GAMEWINDOW_H
