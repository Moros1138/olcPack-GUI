#pragma once

#include <wx/wx.h>

#include "MyFrame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
private:
    MyFrame* frame;
};


