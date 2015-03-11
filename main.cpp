#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#define GLM_SWIZZLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <logic/map/scheme.h>
#include "logic/agents/chest.h"
#include "gamewindow.h"
#include <debug/debug.h>

//#define TESTS

#ifdef TESTS
#define CATCH_CONFIG_RUNNER
#include "tests/catch.hpp"
#endif


#ifdef WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main( int argc, char* const argv[] )
#endif
{
#ifdef TESTS
    int result = Catch::Session().run( argc, argv );
#else
    JargGameWindow gw;
    gw.BaseInit();
    gw.Mainloop();
    return 0;
#endif
}

#ifdef TESTS
#include "tests/tests.hpp"
#endif
