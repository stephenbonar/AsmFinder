// MainWindow.h - Declares the MainWindow class.
//
// Copyright (C) 2024 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <vector>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/textfile.h>
#include "Instruction.h"
#include "Version.h"

enum ID
{
    Open = 1,
    Save = 2,
    Import = 3,
    Export = 4,
    Add = 3
};

class MainWindow : public wxFrame
{
public:
    MainWindow();
private:
    wxString version;
    wxPanel* topPanel;
    wxListView* instructionListView;
    wxTextCtrl *nameTextCtrl;
    wxTextCtrl *descriptionTextCtrl;
    wxButton *addButton;
    std::vector<Instruction> instructions;

    void InitVersion();
   
    void InitMenuBar();

    void InitStatusBar();

    void InitTopPanel();

    void InitInstructionListView();

    void InitFrame();

    void InitEventBindings();

    void OnAbout(wxCommandEvent& event);

    void OnOpen(wxCommandEvent& event);

    void OnImport(wxCommandEvent& event);

    void OnExport(wxCommandEvent& event);

    void OnAdd(wxCommandEvent& event);

    void OnSave(wxCommandEvent& event);

    void OnExit(wxCommandEvent& event);

    void UpdateInstructionListView();

    void MatchInstructions(const Line& line);

    void ParseInstructionDefinition(wxString line);
};

#endif