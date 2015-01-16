#include "gamewindow.h"
#include "mouse.h"
#include "keyboard.h"
#include "settings.h"
#include "jargshader.h"
#include "spritebatch.h"
#include "glm/gtx/transform.hpp"
#include "ui_win.h"

#define MAJOR 2
#define MINOR 1

GameWindow::GameWindow()
{
    GameWindow::wi = this;
}

GameWindow::~GameWindow()
{
    Destroy();
}



bool GameWindow::Init()
{
    LOG(info) << "Jarg initialization start";
    glfwSetErrorCallback([](int a,const char* description){LOG(error) << description;});
    int glfwErrorCode = glfwInit();
    if (!glfwErrorCode)
    {
        LOG(error) << "glfwInit error " << glfwErrorCode;
        return glfwErrorCode;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
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
    glfwSwapInterval(1);

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
        GameWindow::Resize(a, b); Mouse::SetWindowSize(a, b);
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window, double a, double b){
        Mouse::Scroll(b);
    });

    batch = std::make_shared<SpriteBatch>();
    batch->initFreeType();

    fb = std::make_shared<FrameBuffer>();
    tex = std::make_shared<Texture>();
    tex->Empty(glm::vec2(100, 100));

    ws = std::make_shared<WinS>(batch.get());
    ws->windows.push_back(new Win());
}

bool GameWindow::Destroy()
{
   glfwDestroyWindow(window);
   glfwTerminate();
   return true;
}

bool GameWindow::Load()
{
    return true;
}

bool GameWindow::Unload()
{
    return true;
}

void GameWindow::Update()
{
    glfwPollEvents();

    ws->Update();

    Mouse::resetDelta();
}

void GameWindow::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.2, 0.3, 1.0f);



    model = glm::mat4(1.f);
    batch->setUniform(proj * model);
    //batch->renderText(std::to_string(fps.GetCount()).c_str(), 50, 50, 1, 1, glm::vec4(1.f, 1.f, 1.f, 1.f));
    batch->drawRect(glm::vec2(-50.f, -50.f), glm::vec2(100.f, 100.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
    glfwSetWindowTitle(window, std::to_string(fps.GetCount()).c_str());

    ws->Draw();

    batch->render();

    //Mesh m = Quad::GetMesh();

//    BasicShader->Use();
//    CameraSetup(BasicShader->program, *camera);
//    PointLightSetup(BasicShader->program, light);
//    light.position = glm::vec4(sin(gt->current/20.f)*800, 2, cos(gt->current/20.f)*800, 1);

//    icos->World = glm::scale(mat4(1), vec3(0.0,0.0,0.0));
//    icos->Render();

//    //if(!rs->Loaded) {
//        rs->Update(camera->position);
//        glViewport(0, 0, width, height);
//    //    rs->Loaded = true;
//    //}//

//    rs->Draw();


//    glDisable(GL_DEPTH_TEST);
//    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

//    auto MVP = camera->GetOrthoProjection();
//    TextureShader->Use();
//    glUniformMatrix4fv(mvpTex, 1, GL_FALSE, &MVP[0][0]);
//    LinesShader->Use();
//    glUniformMatrix4fv(mvpLine, 1, GL_FALSE, &MVP[0][0]);

//    batched->DrawLine2d(glm::vec2(1), glm::vec2(10), Colors::White);
//    batched->DrawCube3d(vec3(0), vec3(1), Colors::Red);
//    batched->DrawString(vec2(100,100), MetersSpeedString(spd), Colors::Red, *font);
//    spd *= 1.001;

//    LinesShader->Use();
//    glUniformMatrix4fv(mvpLine, 1, GL_FALSE, &camera->VP()[0][0]);
//    test.RenderBounding(*batched);
//    batched->RenderFinallyWorld();

//    ws->Draw();

//    batched->RenderFinally();

    glfwSwapBuffers(window);
    gt.Update(glfwGetTime());
    fps.Update(gt);
}

void GameWindow::Mainloop()
{
    int i =0;
    while(!glfwWindowShouldClose(window))
    {
        Update();
        Draw();
    }
}

void GameWindow::Resize(int w, int h)
{
    if(h == 0)
        h = 1;
    Settings::instance()->resolution = glm::vec2(w, h);
    glViewport(0, 0, w, h);
    GameWindow::wi->proj = glm::mat4(1.f);
    GameWindow::wi->proj = glm::ortho(0.0f, (float)w, (float)h, 0.0f, -1.f, 1.0f);//.perspective(45, (float)w/float(h), 1, 1000);
    GameWindow::wi->model = glm::mat4(1.f);
}

GameWindow *GameWindow::wi = nullptr;
