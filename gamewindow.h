#ifndef JARGGAMEWINDOW_H
#define JARGGAMEWINDOW_H

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
#include "sge/camera.h"
#include "ui/cjarg_main_w.h"
#include "ui/cjarg_list_test.h"
#include "ui/cjarg_perfomance.h"

class JargGameWindow {
public:
    bool BaseInit();
    bool Destroy();
    bool Load();
    bool Unload();

    void BaseUpdate();
    void BaseDraw();

    void Mainloop();
    GameTimer gt;
    FPSCounter fps;
    bool wire = true;

    static void Resize(int w, int h);

    GLFWmonitor *monitor = nullptr;
    GLFWwindow *window = nullptr;
    TextureAtlas atlas;
    std::shared_ptr<Level> level;
    std::shared_ptr<LevelWorker> lworker;

    glm::mat4 ortho_PM;
    static JargGameWindow *wi;
    std::shared_ptr<Texture> tex;
    std::shared_ptr<Creature> me;
    static std::shared_ptr<Camera> cam;
    std::shared_ptr<Mesh> mesh;

    std::shared_ptr<Font> f12;

    JargGameWindow();
    ~JargGameWindow();

    std::chrono::steady_clock::time_point tiker;

    std::shared_ptr<WinS> ws;
    cjarg_main_w *main_w;
    cjarg_perfomance *perf;
    bool fixed = true;


    std::shared_ptr<BasicJargShader> basic, font;
    std::shared_ptr<SpriteBatch> batch;
};

#endif // JARGGAMEWINDOW_H
