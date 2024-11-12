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

/// @brief Represents the main window of the application.
class MainWindow : public wxFrame
{
public:
    /// @brief Default constructor; creates a new instance of MainWindow.
    MainWindow();
private:
    wxString version;
    wxPanel* topPanel;
    wxListView* instructionListView;
    wxTextCtrl *nameTextCtrl;
    wxTextCtrl *descriptionTextCtrl;
    wxButton *addButton;
    std::vector<Instruction> instructions;

    /// @brief Initializes the version string for use in the title and about. 
    void InitVersion();
   
    /// @brief Initialized the menu bar.
    void InitMenuBar();

    /// @brief Initializes the status bar.
    void InitStatusBar();

    /// @brief Initalizes the top panel.
    void InitTopPanel();

    /// @brief Initializes the instruction list view.
    void InitInstructionListView();

    /// @brief Initializes the window frame.
    void InitFrame();

    /// @brief Initalizes the event bindings.
    void InitEventBindings();

    /// @brief Event handler for the Help -> About menu item.
    /// @param event The triggering event.
    void OnAbout(wxCommandEvent& event);

    /// @brief Event handler for the File -> Open menu item.
    /// @param event The triggering event.
    void OnOpen(wxCommandEvent& event);

    /// @brief Event handler for the File -> Import menu item.
    /// @param event The triggering event.
    void OnImport(wxCommandEvent& event);

    /// @brief Event handler for the File -> Export menu item.
    /// @param event The triggering event.
    void OnExport(wxCommandEvent& event);

    /// @brief Event handler for the Add button.
    /// @param event The triggering event.
    void OnAdd(wxCommandEvent& event);

    /// @brief Event handler for the File -> Save menu item.
    /// @param event The triggering event.
    void OnSave(wxCommandEvent& event);

    /// @brief Event handler for the File -> Quit menu item.
    /// @param event The triggering event.
    void OnExit(wxCommandEvent& event);

    /// @brief Updates the instruction list view with the lastest info.
    void UpdateInstructionListView();

    /// @brief Matches the line to any matching instructions.
    /// @param line The line to attempt to match.
    void MatchInstructions(const Line& line);

    /// @brief Parses instruction definitions read from a file.
    /// @param line The line to parse.
    void ParseInstructionDefinition(wxString line);

    /// @brief Clears any previously matches lines from each instruction.
    void ClearInstructionCounts();
};

#endif