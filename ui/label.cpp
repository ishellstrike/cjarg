#include "label.h"
#include "wins.h"
#include "sge/colorextender.h"

Label::Label(WContainer *par) :
    WComponent(par)
{
    onLeftPress = [&](){text.append("x");};
    size = {20,20};
}

Label::~Label()
{

}

void Label::Draw() const
{
    glm::vec2 p = GlobalPos();
    WinS::sb->drawText(text, p, size, WinS::f, Color::White, SpriteBatch::ALIGN_LEFT);
}

void Label::Update()
{

}
