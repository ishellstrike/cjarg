#ifndef WinS_h__
#define WinS_h__
#include "spritebatch.h"
#include "jtexture.h"
#include <vector>
#include "ui/win.h"
#include <list>
#include <glm/glm.hpp>
#include "font.h"

class WinS{
public:
    WinS();
    WinS(SpriteBatch* sb_);
    ~WinS();
    static std::vector<Win*> windows;
    static bool MouseHooked;
    static bool KeyboardHooked;

    void Draw();
    void Update();
    static void ToTop(Win* w);
    static SpriteBatch *sb;
    static Font *f;
};

#endif // WinS_h__
