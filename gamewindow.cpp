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
#include <future>
#include "sge/helper.h"
#include "logic/agents/clickreaction.h"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"

#include "logic/agents/agents.h"

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
    auto www = new cjarg_list_test(ws.get());

    atlas.LoadAll();

    //LOG(info) << bb->getAgent<Chest>()->items[0];

    lworker = std::make_shared<LevelWorker>();
    lworker->SetGenerator(TestGenerator_City1::Generate);
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
    ss->setTexture("error.png");
    database::instance()->registerBlock("error", ss);

    database::instance()->Load();

    tiker = std::chrono::steady_clock::now();

    StaticBlock sb = StaticBlock();
    Block *b = new Block();
    Dynamic *d = new Dynamic();
    d->agents.push_back(std::make_shared<Chest>());
    d->agents.push_back(std::make_shared<Furnance>());
    d->getAgent<Chest>()->items.push_back(Item());
    d->getAgent<Chest>()->items.push_back(Item());
    d->getAgent<Chest>()->items.push_back(Item());
    b->parts = std::unique_ptr<Dynamic>(d);
    sb.etalon = std::unique_ptr<Block>(b);

    std::ostream o_stream(std::cout.rdbuf());
    cereal::JSONOutputArchive arch(o_stream, cereal::JSONOutputArchive::Options::NoIndent());
    arch(sb);
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

    if(Keyboard::isKeyDown(GLFW_KEY_W)){
        me->pos.y += 1;
    }
    if(Keyboard::isKeyDown(GLFW_KEY_S)){
        me->pos.y -= 1;
    }
    if(Keyboard::isKeyDown(GLFW_KEY_A)){
        me->pos.x -= 1;
    }
    if(Keyboard::isKeyDown(GLFW_KEY_D)){
        me->pos.x += 1;
    }

    if(Keyboard::isKeyPress(GLFW_KEY_SPACE)){
        me->Push(glm::vec3(0,0,10));
    }

    if(Keyboard::isKeyPress(GLFW_KEY_LEFT_CONTROL)){
        Mouse::SetFixedPosState(!Mouse::GetFixedPosState());
    }

    if(Keyboard::isKeyPress(GLFW_KEY_F2)){
        wire = wire ? (glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ), false) : (glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ), true);
    }


    if (Keyboard::isKeyDown(GLFW_KEY_LEFT_ALT))
    {
        Mouse::SetFixedPosState(true);
        cam->pitch += Mouse::getCursorDelta().y / 10.f * static_cast<float>(gt.elapsed);
    }
    else
        Mouse::SetFixedPosState(false);

    if (Mouse::isMiddleDown())
    {
       cam->Reset();
    }

    if (Mouse::isRightDown() || Keyboard::isKeyDown(GLFW_KEY_LEFT_ALT))
    {
        cam->yaw += Mouse::getCursorDelta().x / 10.f * static_cast<float>(gt.elapsed);
        cam->viewMatrixDirty = true;
    }

    if(!WinS::MouseHooked)
    {
        if(Mouse::isLeftPressed())
            level->lClick();
        if(Mouse::isRightPressed())
            level->rClick();
        if(Keyboard::isKeyPress(GLFW_KEY_1))
            level->change_at(level->m_selected, "chest");
        if(Keyboard::isKeyPress(GLFW_KEY_2))
            level->change_at(level->m_selected, "fence");
    }

    cam->Update();
    cam->CalculateFrustum(cam->projection, cam->view * cam->model);
    cam->SetLookAt(me->pos);
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
    batch->drawText(string_format("face: %d vert: %d", level->facecount, level->vertcount), {20.f, 20.f}, f12.get(), Color::White);

    batch->drawText(std::to_string(fps.GetCount()).append(" fps"), {5.f, 5.f}, f12.get(), Color::Red);

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
    cam->SetViewport({0, 0, w, h});
    JargGameWindow::wi->ortho_PM = glm::ortho(0.0f, (float)w, (float)h, 0.0f, -1.f, 1.0f);//.perspective(45, (float)w/float(h), 1, 1000);
}

JargGameWindow *JargGameWindow::wi = nullptr;
std::shared_ptr<Camera> JargGameWindow::cam;
