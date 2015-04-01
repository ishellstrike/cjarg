#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#define GLM_SWIZZLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#define TESTS

#ifdef TESTS
#define CATCH_CONFIG_RUNNER
#include "tests/catch.hpp"
#define private public
#endif

#include <logic/map/scheme.h>
#include "logic/agents/chest.h"
#include "gamewindow.h"

#ifdef __WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main( int argc, char* const argv[] )
#endif
{
#ifdef TESTS
    int result = Catch::Session().run( argc, argv );
#else
    if(argc >= 2)
        for(int i = 1; i < argc; i++)
        {
            if(strcmp(argv[i], "-v") == 0)
                Log::max_level = verbose;
            if(strcmp(argv[i], "-i") == 0)
                Log::max_level = info;
            if(strcmp(argv[i], "-e") == 0)
                Log::max_level = error;
            if(strcmp(argv[i], "-f") == 0)
                Log::max_level = fatal;
        }
    JargGameWindow gw;
    gw.BaseInit();
    gw.Mainloop();
    return 0;
#endif
}

#ifdef TESTS
#include "tests/tests.hpp"
#endif
