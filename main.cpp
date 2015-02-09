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
    Dynamic *a = new Dynamic();
    Chest *ch1 = new Chest();
    a->agents.push_back(ch1);
    Dynamic *b = a->instantiate();
    ch1->items.push_back(new Item());

    JargGameWindow gw;
    gw.BaseInit();
    gw.Mainloop();
    return 0;
}
