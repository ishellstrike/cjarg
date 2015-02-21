#ifndef WinS_h__
#define WinS_h__
#include "sge/spritebatch.h"
#include "sge/texture.h"
#include <vector>
#include "ui/win.h"
#include <list>
#include <glm/glm.hpp>
#include "sge/font.h"

class WinS : public WContainer{
public:
    WinS();
    WinS(SpriteBatch* sb_);
    ~WinS();
    static bool MouseHooked;
    static bool KeyboardHooked;

    void Update();
    void ToTop(WComponent *w);
    static SpriteBatch *sb;
    static Font *f;
    static WinS *ws;
    void Draw() const;
};

#endif // WinS_h__
