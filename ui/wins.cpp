#include "ui/wins.h"
#include <vector>
#include <list>
#include "sge/mouse.h"
#include <string>
#include <memory>
#include <algorithm>
#include "sge/prefecences.h"

WinS::WinS() :
    WContainer()
{

}

WinS::WinS(SpriteBatch *sb_) :
    WContainer()
{
    WinS::sb = sb_;
    ws = this;
}

WinS::~WinS()
{
    Items.clear();
}

void WinS::Draw() const
{
    if(Items.size() > 0) {
        for (unsigned int i =0; i< Items.size(); i++)
        {
            if(!Items.at(i)->hidden)
                Items.at(i)->Draw();
            WinS::sb->resetScissor();
        }
    }
}

void WinS::ToTop(WComponent* w) {
    bool b = false;
    int i = 0;
    for (auto iter = Items.begin(); iter != --Items.end(); ++iter) {
        if(iter->get() == w || b) {
            Items[i].swap(Items[i+1]);
            b = true;
        }
        i++;
    }
}

void WinS::Update() {
    MouseHooked = false;

    pos = {0,0};
    size = {RESX, RESY};

    KeyboardHooked = false;
    if(Items.size() > 0)
        Items[Items.size() - 1]->Update();
    KeyboardHooked = true;

    for (auto i = Items.rbegin(); i != Items.rend(); ++i)
    {
        if(!(*i)->hidden)
            (*i)->Update();
    }
}

bool WinS::KeyboardHooked = false;
bool WinS::MouseHooked = false;
WinS *WinS::ws;
SpriteBatch *WinS::sb = nullptr;
Font *WinS::f = nullptr;

