#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#define GLM_SWIZZLE
#include "gamewindow.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "logic/agents/chest.h"
#ifdef WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main()
#endif
{
    Dynamic a;
    a.agents.push_back(Chest());
    a.getDynamic<Chest>()->items.push_back(Item());
    auto b = a;
    b.getDynamic<Chest>()->items.push_back(Item());

    JargGameWindow gw;
    gw.BaseInit();
    gw.Mainloop();
    return 0;
}
