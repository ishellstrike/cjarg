#define GLM_SWIZZLE
#include "gamewindow.h"
#include "sge/mouse.h"
#include "sge/keyboard.h"
#include "sge/prefecences.h"
#include "sge/shader.h"
#include "sge/spritebatch.h"
#include "glm/gtx/transform.hpp"
#include "sge_ui/win.h"
#include "sge/colorextender.h"
#include "sge/textureatlas.h"
#include <thread>
#include <chrono>
#include "logic/map/trivialgenerator.h"
#include <future>
#include "sge/helper.h"
#include "logic/agents/clickreaction.h"
#include "sge/geometry/cube.h"

#include "logic/agents/agents.hpp"

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

    LOG(verbose) << "Block size " << to_traf_string(sizeof(std::shared_ptr<Block>) + sizeof(Block));
    LOG(verbose) << "Sector minimal size " << to_traf_string(sizeof(std::shared_ptr<Block>)*RX*RY*RZ);
    LOG(verbose) << "Sector dim " << RX << "x" << RY << "x" << RZ;


    glfwSetErrorCallback([](int a, const char* description){(void)a; LOG(error) << description;});
    int glfwErrorCode = glfwInit();
    if (!glfwErrorCode)
    {
        LOG(fatal) << "glfwInit error " << glfwErrorCode;
        return false;
    }

    //glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    monitor = nullptr;

    window = glfwCreateWindow(RESX, RESY, string_format("cjarg %s %s", "v", "d").c_str(), monitor, nullptr);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    Keyboard::Initialize();
    glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancode, int action, int mods){
        (void)win;
        Keyboard::SetKey(key, scancode, action, mods);
    });
    Mouse::initialize(window);
    cam = std::make_shared<Camera>();
    cam->SetPosition({40,40,30});
    cam->setLookAt({0,0,0});
    Resize(RESX, RESY);
    //Mouse::SetFixedPosState(true);
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos){
        (void)window;
        Mouse::SetCursorPos(xpos, ypos);
    });
    glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int entered){
        (void)window;
        Mouse::cursorClientArea(entered);
    });
    glfwSetWindowFocusCallback(window, [](GLFWwindow *window, int focused){
        (void)window;
        Mouse::windowFocus(focused);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int a, int b, int c){
        (void)window;
        Mouse::SetButton(a, b, c);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int a, int b){
        (void)window;
        JargGameWindow::Resize(a, b); Mouse::setWindowSize(a, b);
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset){
        (void)window;
        (void)xoffset;
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
    perf = new cjarg_perfomance(ws.get());
    build = new cjarg_base_mode_main(ws.get());
    ws->ToTop(ww);

    atlas.LoadAll();

    //LOG(info) << bb->getAgent<Chest>()->items[0];

    database::instance()->Load();

    lworker = std::make_shared<LevelWorker>();
    lworker->SetGenerator(TrivialGenerator::Generate);
    level = std::make_shared<Level>(*lworker);

    me = std::shared_ptr<Creature>(database::instance()->getStaticCreature("human")->etalon->instantiate());
    me->pos.z = 32;
    level->lw.mem[Point(0,0)] = std::shared_ptr<Sector>(new Sector());
    level->lw.mem[Point(0,0)]->Init();
    level->lw.mem[Point(0,0)]->creatures.push_back(me);
    for(auto a : level->colony.team)
        level->lw.mem[Point(0,0)]->creatures.push_back(a);

    std::shared_ptr<Material> mat = std::make_shared<Material>();

    tiker = std::chrono::steady_clock::now();
    mesh = Cube::getMesh();
    mesh->Unindex();
    mesh->computeNormal();
    mesh->material = mat;
    mesh->shader = level->basic;
    mesh->Bind();

    return true;
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
        me->Push(cam->Forward);
    }
    if(Keyboard::isKeyDown(GLFW_KEY_S)){
        me->Push(cam->Backward);
    }
    if(Keyboard::isKeyDown(GLFW_KEY_A)){
       me->Push(cam->Left);
    }
    if(Keyboard::isKeyDown(GLFW_KEY_D)){
        me->Push(cam->Right);
    }

    if(Keyboard::isKeyPress(GLFW_KEY_SPACE)){
        me->Push(glm::vec3(0,0,10));
    }

    if(Keyboard::isKeyPress(GLFW_KEY_LEFT_CONTROL)){
        Mouse::SetFixedPosState(!Mouse::GetFixedPosState());
    }

    if(Keyboard::isKeyPress(GLFW_KEY_F1)){
        fixed = !fixed;
        if(fixed) tiker = std::chrono::steady_clock::now();
    }
    if(Keyboard::isKeyPress(GLFW_KEY_F2)){
        wire = wire ? (glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ), false) : (glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ), true);
    }

    if(Keyboard::isKeyPress(GLFW_KEY_F5)){
        build->hidden = !build->hidden;
    }

    if(Keyboard::isKeyPress(GLFW_KEY_MINUS)) {
        level->slice(level->slice() - 1);
    }
    if(Keyboard::isKeyPress(GLFW_KEY_EQUAL)) {
        level->slice(level->slice() + 1);
    }

    if(Keyboard::isKeyPress(GLFW_KEY_ESCAPE)) {
        ws->CloseTop();
    }

    if (Keyboard::isKeyDown(GLFW_KEY_LEFT_ALT))
    {
        Mouse::SetFixedPosState(true);
        cam->setPitch(cam->getPitch() + Mouse::getCursorDelta().y / 1000.f);
    }
    if(Mouse::isRightDown() || Keyboard::isKeyDown(GLFW_KEY_LEFT_ALT))
    {
        Mouse::SetFixedPosState(true);
        cam->setYaw(cam->getYaw() + Mouse::getCursorDelta().x / 1000.f);
    }
    else
        Mouse::SetFixedPosState(false);

    if (Mouse::isMiddleDown())
    {
       cam->Reset();
    }

    if(!WinS::MouseHooked)
    {
        auto ord = build->GetCurOrder();

        switch (ord) {
        case cjarg_base_mode_main::ORD_RPG:
            if(Mouse::isLeftPressed())
                level->lClick();
            if(Mouse::isRightPressed())
                level->rClick();
            break;
        case cjarg_base_mode_main::ORD_DIG:
            if(Mouse::isLeftPressed())
                level->colony.orders.active.push_back(std::make_shared<Order>(Order::Dig, level->m_selected));
            break;
        case cjarg_base_mode_main::ORD_BUILD:
            if(Mouse::isLeftPressed())
                level->colony.orders.active.push_back(std::make_shared<Order>(Order::Build, level->m_selected));
            break;
        default:
            break;
        }

        if(Keyboard::isKeyPress(GLFW_KEY_1))
            level->change_at(level->m_selected, "chest");
        if(Keyboard::isKeyPress(GLFW_KEY_2))
            level->change_at(level->m_selected, "fence");
    }

    cam->Update();
    cam->CalculateFrustum();

    auto t_look = cam->getLookAt();
    cam->setLookAt(glm::mix(t_look, me->pos, gt.elapsed*10));

    world_tick += gt.elapsed;
    if(world_tick >= 0.05)
    {
        world_tick = 0;
        level->Preload({cam->getPosition().x / RX, cam->getPosition().y / RY}, 7);
        level->Update(cam, gt);
    }

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
    mesh->World = glm::translate(glm::mat4(1), me->pos + glm::vec3(0,0,1));
    mesh->Render(cam->getVP());


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    batch->setUniform(ortho_PM);
    batch->drawText(cam->getFullDebugDescription(), {10.f, 100.f}, f12.get(), Color::White);
    batch->drawText(string_format("face: %d vert: %d", level->facecount, level->vertcount), {20.f, 20.f}, f12.get(), Color::White);

    batch->drawText(string_format("%d fps th %d", fps.GetCount(), LevelWorker::th), {5.f, 5.f}, f12.get(), Color::Red);

    ws->Draw();
    if(!Mouse::GetFixedPosState()) {
        if(Mouse::state == Mouse::STATE_MOUSE)
            batch->drawQuadAtlas(Mouse::getCursorPos(), {32,32}, *TextureAtlas::tex, TextureAtlas::refs["cur_mouse.png"], Color::White);
        else
            batch->drawQuadAtlas(Mouse::getCursorPos(), {32,32}, *TextureAtlas::tex, TextureAtlas::refs["cur_resize.png"], Color::White);
    }
    Mouse::state = Mouse::STATE_MOUSE;
    batch->render();

    glfwSwapBuffers(window);
    gt.Update(glfwGetTime());
    fps.Update(gt);
    perf->UpdateTimer(fps, gt);
}

void JargGameWindow::Mainloop()
{
    int i =0;
    while(!glfwWindowShouldClose(window))
    {
        BaseUpdate();
        BaseDraw();
        if(fixed)
        {
           // tiker += std::chrono::microseconds(100000/6);
          //  std::this_thread::sleep_until(tiker);
        }
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
