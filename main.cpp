#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#include "gamewindow.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

#ifdef WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main()
#endif
{
    GameWindow gw;
    gw.Init();

    gw.Mainloop();

    return 0;
}
