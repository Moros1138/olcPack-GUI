#pragma once

#include <wx/wx.h>
class MyFrame : public wxFrame
{
public:
    MyFrame();

private: // event handlers
    void OnDropFiles(wxDropFilesEvent& event);
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);

private: // objects
    wxBoxSizer*    pSizer;
    wxTextCtrl* dropTarget;
    wxTextCtrl* textCtrl;

    wxMenu*    menuFile;
    wxMenu*    menuHelp;
    wxMenuBar* menuBar;

};