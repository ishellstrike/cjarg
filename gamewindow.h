#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>
#include "sge/logger.h"
#include "sge/shader.h"
#include "sge/spritebatch.h"
#include "ui/wins.h"
#include "sge/fpscounter.h"
#include "sge/gametimer.h"
#include "sge/textureatlas.h"
#include "logic/map/level.h"
#include "logic/map/levelworker.h"
#include "logic/base/database.h"
#include "sge/font.h"

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
    std::shared_ptr<Level> level;
    std::shared_ptr<LevelWorker> lworker;
    glm::vec3 cam;

    glm::mat4 view, proj, model;
    static GameWindow *wi;
    std::shared_ptr<Texture> tex;
    std::shared_ptr<Creature> me;

    std::shared_ptr<Font> f12;

    GameWindow();
    ~GameWindow();

    std::shared_ptr<WinS> ws;

    std::shared_ptr<JargShader> basic, font;
    std::shared_ptr<SpriteBatch> batch;
};

#endif // GAMEWINDOW_H
