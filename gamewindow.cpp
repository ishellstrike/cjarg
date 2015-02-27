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
#include "logic/agents/agent.h"
#include "logic/agents/chest.h"
#include <future>
#include "sge/helper.h"
#include "logic/agents/clickreaction.h"

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    Keyboard::Initialize();
    glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancode, int action, int mods){
        Keyboard::SetKey(key, scancode, action, mods);
    });
    Mouse::initialize(window);
    cam = std::make_shared<Camera>();
    cam->SetPosition({40,40,30});
    cam->SetLookAt({0,0,0});
    Resize(RESX, RESY);
    //Mouse::SetFixedPosState(true);
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos){
        Mouse::SetCursorPos(xpos, ypos);
    });
    glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int entered){
        Mouse::cursorClientArea(entered);
    });
    glfwSetWindowFocusCallback(window, [](GLFWwindow *window, int focused){
        Mouse::windowFocus(focused);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int a, int b, int c){
        Mouse::SetButton(a, b, c);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int a, int b){
        JargGameWindow::Resize(a, b); Mouse::setWindowSize(a, b);
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset){
        Mouse::Scroll(yoffset);
    });

    batch = std::make_shared<SpriteBatch>();

    tex = std::make_shared<Texture>();

    ws = std::make_shared<WinS>(batch.get());

    f12 = std::make_shared<Font>();
    f12->initFreeType(12);
    f12->renderAtlas();

    ws->f = f12.get();

    new Win(ws.get());
    cjarg_main_w *ww = new cjarg_main_w(ws.get());
    ww->size = {200,200};
    auto www = new cjarg_list_test(ws.get());
    www->size = {200,200};

    atlas.LoadAll();

    //LOG(info) << bb->getAgent<Chest>()->items[0];

    lworker = std::make_shared<LevelWorker>();
    lworker->SetGenerator(TrivialGenerator::Generate);
    level = std::make_shared<Level>(*lworker);

    me = std::make_shared<Creature>();
    me->pos.z = 32;
    level->lw.mem[Point(0,0)] = std::shared_ptr<Sector>(new Sector());
    level->lw.mem[Point(0,0)]->Init();
    level->lw.mem[Point(0,0)]->creatures.push_back(me.get());

    StaticBlock *ss = new StaticBlock();
    ss->setTexture(0);
    ss->transparent = true;
    database::instance()->registerBlock("air", ss);

    ss = new StaticBlock();
    ss->setTexture("mc_dirt.png");
    database::instance()->registerBlock("dirt", ss);

    ss = new StaticBlock();
    ss->setTexture(StaticBlock::SIDE_TOP, "mc_grass.png");
    ss->setTexture(StaticBlock::SIDE_BOTTOM, "mc_dirt.png");
    ss->setSideTexture("mc_grass_side.png");
    ss->r_click = std::unique_ptr<ClickReactionTest>(new ClickReactionTest());
    database::instance()->registerBlock("grass", ss);

    ss = new StaticBlock();
    ss->setTexture("error.png");
    database::instance()->registerBlock("error", ss);

    ss = new StaticBlock();
    ss->setTexture("fence_s.png");
    ss->transparent = true;
    database::instance()->registerBlock("fence", ss);

    ss = new StaticBlock();
    ss->setTexture(StaticBlock::SIDE_FRONT, "f.png");
    ss->setTexture(StaticBlock::SIDE_BACK, "b.png");
    ss->setTexture(StaticBlock::SIDE_TOP, "t.png");
    ss->setTexture(StaticBlock::SIDE_BOTTOM, "bot.png");
    ss->setTexture(StaticBlock::SIDE_LEFT, "l.png");
    ss->setTexture(StaticBlock::SIDE_RIGHT, "r.png");
    database::instance()->registerBlock("test", ss);

    ss = new StaticBlock();
    ss->setSideTexture("chest_side.png");
    ss->setTexture(StaticBlock::SIDE_BOTTOM, "chest.png");
    ss->setTexture(StaticBlock::SIDE_TOP, "chest.png");
    ss->setTexture(StaticBlock::SIDE_FRONT, "chest_front.png");
    database::instance()->registerBlock("chest", ss);

    tiker = std::chrono::steady_clock::now();
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
        glm::vec3 t = (glm::vec3(0, 0, -1) * cam->rotation_quaternion * (float)gt.elapsed) * 15.f;
        me->Push(glm::vec3(t.x, t.y, 0.2));
    }
    if(Keyboard::isKeyDown(GLFW_KEY_S)){
        glm::vec3 t = (glm::vec3(0, 0, 1) * cam->rotation_quaternion * (float)gt.elapsed) * 15.f;
        me->Push(glm::vec3(t.x, t.y, 0.2));
    }
    if(Keyboard::isKeyDown(GLFW_KEY_A)){
        glm::vec3 t = (glm::vec3(-1, 0, 0) * cam->rotation_quaternion * (float)gt.elapsed) * 15.f;
        me->Push(glm::vec3(t.x, t.y, 0.2));
    }
    if(Keyboard::isKeyDown(GLFW_KEY_D)){
        glm::vec3 t = (glm::vec3(1, 0, 0) * cam->rotation_quaternion * (float)gt.elapsed) * 15.f;
        me->Push(glm::vec3(t.x, t.y, 0.2));
    }

    if(Keyboard::isKeyPress(GLFW_KEY_SPACE)){
        me->Push(glm::vec3(0,0,10));
    }

    if(Keyboard::isKeyPress(GLFW_KEY_LEFT_CONTROL)){
        Mouse::SetFixedPosState(!Mouse::GetFixedPosState());
    }
    cam->position = me->pos + glm::vec3(0,0,2);

    if(Keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT)){
        cam->camera_scale = 50.0F;
    } else {
        cam->camera_scale = 10.0F;
    }

    if(Mouse::GetFixedPosState())
    {
        cam->Move2D(Mouse::getCursorDelta().x, Mouse::getCursorDelta().y, &gt);
    }
    if(Keyboard::isKeyPress(GLFW_KEY_1))
    {
        level->change_at(level->m_selected, "chest");
    }
    if(Keyboard::isKeyPress(GLFW_KEY_2))
    {
        level->change_at(level->m_selected, "fence");
    }


    if(Mouse::isLeftPressed())
    {
        level->lClick();
    }
    if(Mouse::isRightPressed())
        level->rClick();


    cam->Update();
    cam->CalculateFrustum(cam->projection, cam->view * cam->model);
    level->Preload({cam->position.x / RX, cam->position.y / RY}, 7);
    level->Update(cam, gt);

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
    glClearColor(Color::CornflowerBlue.r,Color::CornflowerBlue.g,Color::CornflowerBlue.b,0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    level->Render(cam);


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    batch->setUniform(ortho_PM);
    batch->drawText(cam->getFullDebugDescription(), {10.f, 100.f}, f12.get(), Color::White);
    batch->drawText(string_format("face: %d vert: %d", level->facecount, level->vertcount), {200.f, 100.f}, f12.get(), Color::White);

    batch->drawText(std::to_string(fps.GetCount()).append(" fps"), {50.f, 50.f}, f12.get(), Color::Red);

    ws->Draw();
    if(!Mouse::GetFixedPosState())
        if(Mouse::state == Mouse::STATE_MOUSE)
            batch->drawQuadAtlas(Mouse::getCursorPos(), {32,32}, *TextureAtlas::tex, TextureAtlas::refs["cur_mouse.png"], Color::White);
        else
            batch->drawQuadAtlas(Mouse::getCursorPos(), {32,32}, *TextureAtlas::tex, TextureAtlas::refs["cur_resize.png"], Color::White);
    Mouse::state = Mouse::STATE_MOUSE;
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
        tiker += std::chrono::microseconds(100000/6);
        std::this_thread::sleep_until(tiker);
    }
}

void JargGameWindow::Resize(int w, int h)
{
    if(h == 0)
        h = 1;
    Prefecences::Instance()->resolution = glm::vec2(w, h);
    glViewport(0, 0, w, h);
    cam->SetViewport(0, 0, w, h);
    JargGameWindow::wi->ortho_PM = glm::ortho(0.0f, (float)w, (float)h, 0.0f, -1.f, 1.0f);//.perspective(45, (float)w/float(h), 1, 1000);
}

JargGameWindow *JargGameWindow::wi = nullptr;
std::shared_ptr<Camera> JargGameWindow::cam;
