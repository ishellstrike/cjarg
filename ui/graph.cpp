#include "graph.h"
#include "sge/spritebatch.h"
#include "wins.h"
#include "sge/colorextender.h"
#include <algorithm>

Graph::Graph(WContainer *par) :
    WComponent(par)
{
    data.resize(dsize);
    size = {100,100};
}

void Graph::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    float x = 1;
    float ysize = size.y * 0.8f;
    auto max = *std::max_element(std::begin(data), std::end(data));
    auto min = *std::min_element(std::begin(data), std::end(data));
    for(int b = dpos + 1; b < dsize + dpos; b++, x+= 1)
    {
        auto a = b % dsize;
        auto preval = (1-(((data[a-1])-min) / (max-min)))*ysize;
        auto val = (1-(((data[a])-min) / (max-min)))*ysize;
        sb.drawLine(glm::vec2((size.x - 1)/(float)dsize * x, preval) + pos,
                    glm::vec2(size.x/(float)dsize * x, val) + pos, 1, WinS::color.border_up);
    }

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WinS::color.border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WinS::color.border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WinS::color.border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WinS::color.border_down);

    sb.drawText(std::to_string(max), {pos.x, pos.y + 2}, WinS::f, WinS::color.text);
    sb.drawText(std::to_string(min), {pos.x, pos.y + size.y - 15}, WinS::f, WinS::color.text);

    WComponent::Draw();
}

void Graph::Update()
{
    WComponent::Update();
}

void Graph::AddValue(float a)
{
    data[dpos] = a;
    dpos++;
    if(dpos >= dsize)
        dpos = 0;
}

