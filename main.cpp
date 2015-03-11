#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#define GLM_SWIZZLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <logic/map/scheme.h>
#include "logic/agents/chest.h"
#include "gamewindow.h"

#ifdef WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main( int argc, char* const argv[] )
#endif
{
    JargGameWindow gw;
    gw.BaseInit();
    gw.Mainloop();
    return 0;
}
