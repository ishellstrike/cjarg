#include "WinS.h"
#include <vector>
#include <list>
#include "mouse.h"
#include <string>

WinS::WinS()
{

}

WinS::WinS(SpriteBatch *sb_)
{
    WinS::sb = sb_;
}

WinS::~WinS()
{
    if(windows.size() > 0) {
        for(unsigned int i=0 ;i< windows.size(); i++)
            delete windows.at(i);
    }
    windows.clear();
}

void WinS::Draw()
{
    if(windows.size() > 0) {
        for (unsigned int i =0; i< windows.size(); i++)
            windows.at(i)->Draw();
    }
}

void WinS::ToTop(Win* w) {
    std::vector<Win*>::iterator iter;
    bool b = false;
    int i =0;  
    for (iter = windows.begin() ; iter != --windows.end(); ++iter) {
        if(*iter == w || b) {
            Win* temp = w;
            windows[i] = windows[i+1];
            windows[i+1] = temp;
            b = true;
        }
        i++;
    }
}

void WinS::Update() {
    MouseHooked = false;

    KeyboardHooked = false;
    if(windows.size() > 0)
        windows[windows.size() - 1]->Update();
    KeyboardHooked = true;

    if(windows.size() > 0) {
        for (int i =windows.size() - 2; i >= 0; i--)
            windows[i]->Update();
    }
}

std::vector<Win*> WinS::windows;

bool WinS::KeyboardHooked;
bool WinS::MouseHooked;
SpriteBatch* WinS::sb;

