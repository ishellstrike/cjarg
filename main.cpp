#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#define GLM_SWIZZLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <logic/map/scheme.h>
#include "logic/agents/chest.h"
#include "gamewindow.h"

#define CATCH_CONFIG_RUNNER
#include "tests/catch.hpp"

#ifdef WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main( int argc, char* const argv[] )
#endif
{
    int result = Catch::Session().run( argc, argv );

    JargGameWindow gw;
    gw.BaseInit();
    gw.Mainloop();
    return 0;
}

#include "tests/scheme_tests.h"
