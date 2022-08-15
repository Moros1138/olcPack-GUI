#include "MyFrame.h"

#include <wx/arrstr.h>
#include <wx/dir.h>

#include <iostream>

enum
{
    ID_Hello = 1,
    ID_Clear
};

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello, World")
{
    menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(ID_Clear, "&Clear\tEsc", "Clear the list");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    

    pSizer = new wxBoxSizer(wxVERTICAL);
    dropTarget = new wxTextCtrl(
        this,
        wxID_ANY,
        _("Drop files onto me!"),
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_MULTILINE|wxTE_READONLY
    );
    dropTarget->DragAcceptFiles(true);
    pSizer->Add(dropTarget, 1, wxEXPAND, 0);

    SetSizer(pSizer);
    Layout();
    Center();

    dropTarget->Connect(
        wxEVT_DROP_FILES,
        wxDropFilesEventHandler(MyFrame::OnDropFiles),
        NULL,
        this
    );

    // Set Event Handlers
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnClear, this, ID_Clear);
}

void MyFrame::OnDropFiles(wxDropFilesEvent& event)
{
    if(event.GetNumberOfFiles() > 0)
    {
        wxString* dropped = event.GetFiles();
        wxASSERT(dropped);

        wxString name;
        wxArrayString files;

        for(int i = 0; i < event.GetNumberOfFiles(); i++)
        {
            name = dropped[i];
            
            if(wxFileExists(name))
            {
                files.push_back(name);
                continue;
            }

            if(wxDirExists(name))
            {
                wxDir::GetAllFiles(name, &files);
                continue;
            }
        }

        textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
        wxASSERT(textCtrl);
        textCtrl->Clear();
        
        for(size_t i = 0; i < files.size(); i++)
        {
            // std::cout << files[i] << std::endl;
            *textCtrl << files[i] << wxT('\n');
        }
            
    }
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello, World example", "About Hello, World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello, world from wxWidgets!");
}

void MyFrame::OnClear(wxCommandEvent& event)
{
    dropTarget->Clear();
}
