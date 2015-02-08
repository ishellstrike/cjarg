#define GLM_SWIZZLE
#include "gamewindow.h"
#include "sge/mouse.h"
#include "sge/keyboard.h"
#include "sge/prefecences.h"
#include "sge/shader.h"
#include "sge/spritebatch.h"
#include "glm/gtx/transform.hpp"
#include "ui/win.h"
#include "sge/colorextender.h"
#include "sge/textureatlas.h"
#include <thread>
#include <chrono>
#include "logic/map/trivialgenerator.h"
#include "jhelper.inl"
#include "logic/agents/agent.h"
#include "logic/agents/chest.h"
#include <future>

#define MAJOR 2
#define MINOR 1

JargGameWindow::JargGameWindow()
{
    JargGameWindow::wi = this;
}

JargGameWindow::~JargGameWindow()
{
    Destroy();
}



bool JargGameWindow::BaseInit()
{
    LOG(info) << "Jarg initialization start";
    LOG(info) << "User-preferred locale setting is " << std::locale("").name().c_str();
    LOG(info) << "Hardware concurrency " << std::thread::hardware_concurrency();
    glfwSetErrorCallback([](int a,const char* description){LOG(error) << description;});
    int glfwErrorCode = glfwInit();
    if (!glfwErrorCode)
    {
        LOG(error) << "glfwInit error " << glfwErrorCode;
        return false;
    }
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    monitor = nullptr;

    window = glfwCreateWindow(RESX, RESY, "cjarg", monitor, nullptr);
    if (!window)
    {
        glfwTerminate();
        LOG(fatal) << "GLFW window fatal error. Minimum feature level " << MAJOR << "." << MINOR;
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    int err = glewInit();
    if (err != GLEW_OK)
    {
        LOG(fatal) << "GLEW init fatal etrror";
        LOG(fatal) << "GLEW Error : " << std::string((const char*)glewGetErrorString(err));
        return false;
    }


    int glVersion[2] = {-1, -1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    LOG(info) << "Renderer: " << glGetString(GL_RENDERER);
    LOG(info) << "Vendor: " << glGetString(GL_VENDOR);
    LOG(info) << "Version: " << glGetString(GL_VERSION);
    LOG(info) << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
    LOG(info) << "using OpenGL: " << glVersion[0] << "." << glVersion[1];
    LOG(info) << "GLFW: " << glfwGetVersionString();
    LOG(info) << "GLEW: " << glewGetString(GLEW_VERSION);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Keyboard::Initialize();
    glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancode, int action, int mods){
        Keyboard::SetKey(key, scancode, action, mods);
    });
    Mouse::Initialize(window);
    cam = std::make_shared<Camera>();
    cam->SetPosition({40,40,30});
    cam->SetLookAt({0,0,0});
    Resize(RESX, RESY);
    //Mouse::SetFixedPosState(true);
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos){
        Mouse::SetCursorPos(xpos, ypos);
    });
    glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int entered){
        Mouse::CursorClientArea(entered);
    });
    glfwSetWindowFocusCallback(window, [](GLFWwindow *window, int focused){
        Mouse::WindowFocus(focused);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int a, int b, int c){
        Mouse::SetButton(a, b, c);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int a, int b){
        JargGameWindow::Resize(a, b); Mouse::SetWindowSize(a, b);
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset){
        Mouse::Scroll(yoffset);
    });

    batch = std::make_shared<SpriteBatch>();

    tex = std::make_shared<Texture>();

    ws = std::make_shared<WinS>(batch.get());
    ws->windows.push_back(new Win());

    atlas.LoadAll();

    //LOG(info) << bb->getAgent<Chest>()->items[0];

    lworker = std::make_shared<LevelWorker>();
    lworker->SetGenerator(TrivialGenerator::Generate);
    level = std::make_shared<Level>(*lworker);
    level->Preload({0,0}, 6);

    me = std::make_shared<Creature>();
    me->pos.z = 32;
    //level->active[Point(0,0)]->creatures.push_back(me.get());

    f12 = std::make_shared<Font>();
    f12->initFreeType(12);
    f12->renderAtlas();

    ws->f = f12.get();
}

bool JargGameWindow::Destroy()
{
   database::drop();
   glfwDestroyWindow(window);
   glfwTerminate();
   return true;
}

bool JargGameWindow::Load()
{
    return true;
}

bool JargGameWindow::Unload()
{
    return true;
}

void JargGameWindow::BaseUpdate()
{
    glfwPollEvents();

    if(Keyboard::isKeyDown(GLFW_KEY_UP))
        me->pos.y -= 0.1;
    if(Keyboard::isKeyDown(GLFW_KEY_DOWN))
        me->pos.y += 0.1;
    if(Keyboard::isKeyDown(GLFW_KEY_LEFT))
        me->pos.x -= 0.1;
    if(Keyboard::isKeyDown(GLFW_KEY_RIGHT))
        me->pos.x += 0.1;

    if(Keyboard::isKeyDown(GLFW_KEY_W)){
        cam->Move(FORWARD, &gt);
    }
    if(Keyboard::isKeyDown(GLFW_KEY_S)){
        cam->Move(BACK, &gt);
    }
    if(Keyboard::isKeyDown(GLFW_KEY_A)){
        cam->Move(LEFT, &gt);
    }
    if(Keyboard::isKeyDown(GLFW_KEY_D)){
        cam->Move(RIGHT, &gt);
    }

    if(Keyboard::isKeyPress(GLFW_KEY_LEFT_CONTROL)){
        Mouse::SetFixedPosState(!Mouse::GetFixedPosState());
    }

    if(Keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT)){
        cam->camera_scale = 50.0F;
    } else {
        cam->camera_scale = 10.0F;
    }

    if(Mouse::GetFixedPosState())
        cam->Move2D(Mouse::GetCursorDelta().x, Mouse::GetCursorDelta().y, &gt);

    cam->Update();
    level->Preload({cam->position.x / RX, cam->position.y / RY}, 6);

    auto bl = level->block(me->pos);
    //if(bl && bl->id() == 0)
       // me->pos.z -= 0.1;
    me->pos.z = level->ground(me->pos) + 1;

    if(Mouse::isWheelUp())
    {
        level->zoom *= 1.1;
    }
    if(Mouse::isWheelDown())
    {
        level->zoom /= 1.1;
    }

    ws->Update();
    Mouse::resetDelta();
}

void JargGameWindow::BaseDraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    level->Render(cam);


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    batch->setUniform(proj * model);
    batch->drawText(cam->getFullDebugDescription(), 10, 100, f12.get(), Color::White);
    batch->drawText(string_format("face: %d vert: %d", level->facecount, level->vertcount), 200, 100, f12.get(), Color::White);

    batch->drawText(std::to_string(fps.GetCount()), 50, 50, f12.get(), Color::Red);

    ws->Draw();
    batch->render();

    glfwSwapBuffers(window);
    gt.Update(glfwGetTime());
    fps.Update(gt);
}

void JargGameWindow::Mainloop()
{
    int i =0;
    while(!glfwWindowShouldClose(window))
    {
        BaseUpdate();
        BaseDraw();
        //std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void JargGameWindow::Resize(int w, int h)
{
    if(h == 0)
        h = 1;
    Prefecences::Instance()->resolution = glm::vec2(w, h);
    glViewport(0, 0, w, h);
    cam->SetViewport(0, 0, w, h);
    JargGameWindow::wi->proj = glm::ortho(0.0f, (float)w, (float)h, 0.0f, -1.f, 1.0f);//.perspective(45, (float)w/float(h), 1, 1000);
    JargGameWindow::wi->proj_per = glm::perspective(45.0f, w /(float) h, 0.1f, 1000.f);
    JargGameWindow::wi->model = glm::mat4(1.f);
    JargGameWindow::wi->view = glm::lookAt(glm::vec3(70,70,-30), glm::vec3(0,0,0), glm::vec3(0,0,-1));
}

JargGameWindow *JargGameWindow::wi = nullptr;
std::shared_ptr<Camera> JargGameWindow::cam;
