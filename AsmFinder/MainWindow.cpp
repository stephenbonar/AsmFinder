// MainWindow.cpp - Defines the MainWindow class.
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

#include "MainWindow.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "AsmFinder")
{
    InitVersion();
    InitMenuBar();
    InitStatusBar();
    InitTopPanel();
    InitInstructionListView();
    InitFrame();
    InitEventBindings();
}

void MainWindow::InitVersion()
{
    version << 'v' << VERSION_MAJOR << "." << VERSION_MINOR;
    version << "." << VERSION_PATCH << ' ' << PROGRAM_RELEASE << '\n';
    wxString title;
    title << PROGRAM_NAME << " " << version;
    SetTitle(title);
}

void MainWindow::InitMenuBar()
{
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(ID::Open, "&Open...\tCtrlO",
                    "Open an assembly source file");
    fileMenu->Append(ID::Save, "&Save...\tCtrlO",
                    "Saves the results as an assembly source file");
    fileMenu->Append(ID::Import, "&Import...\tCtrlI",
                    "Imports a list of instructions");
    fileMenu->Append(ID::Export, "&Export...\tCtrlE",
                    "Exports a list of instructions");
    fileMenu->Append(wxID_EXIT);
 
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");
 
    SetMenuBar(menuBar);
}

void MainWindow::InitStatusBar()
{
    CreateStatusBar();
    SetStatusText("Ready");
}

void MainWindow::InitTopPanel()
{
    topPanel = new wxPanel{ this, wxID_ANY, wxDefaultPosition };

    wxStaticText *nameLabel = new wxStaticText{ topPanel, wxID_ANY, "Name" };
    nameTextCtrl = new wxTextCtrl(topPanel, wxID_ANY);
    wxStaticText *descriptionLabel = new wxStaticText{ topPanel, wxID_ANY, 
                                                       "Description" };
    descriptionTextCtrl = new wxTextCtrl(topPanel, wxID_ANY);
    addButton = new wxButton(topPanel, ID::Add, "Add");

    wxBoxSizer* topSizer = new wxBoxSizer{ wxHORIZONTAL };
    topSizer->Add(nameLabel);
    topSizer->Add(nameTextCtrl);
    topSizer->Add(descriptionLabel);
    topSizer->Add(descriptionTextCtrl);
    topSizer->Add(addButton);
    topPanel->SetSizerAndFit(topSizer);
}

void MainWindow::InitInstructionListView()
{
    instructionListView = new wxListView{ this, wxID_ANY, 
                                   wxDefaultPosition, wxSize{600, 400} };
    instructionListView->AppendColumn("Instruction");
    instructionListView->AppendColumn("Description");
    instructionListView->AppendColumn("Found");
}

void MainWindow::InitFrame()
{
    wxBoxSizer* frameSizer = new wxBoxSizer{ wxVERTICAL };
    frameSizer->Add(topPanel, 0, wxEXPAND);
    frameSizer->Add(instructionListView, 1, wxEXPAND);
    SetSizerAndFit(frameSizer);
}

void MainWindow::InitEventBindings()
{
    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, ID::Open);
    Bind(wxEVT_MENU, &MainWindow::OnSave, this, ID::Save);
    Bind(wxEVT_MENU, &MainWindow::OnImport, this, ID::Import);
    Bind(wxEVT_MENU, &MainWindow::OnExport, this, ID::Export);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MainWindow::OnAdd, this, ID::Add);
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
    wxFileDialog dialog(this);

    if(dialog.ShowModal() != wxID_OK) 
        return;

    wxString path = dialog.GetPath();
    wxTextFile asmFile;
    asmFile.Open(path);

    // Initial: 3:11:83 (1682.6 lines per second (321,379 lines/ 191 seconds))
    // Elapsed time adding break: 3:11:83
    // Elapsed time eliminating copy on Instruction::Match(): 3:00:72.
    // TODO: Speed this up further.

    int currentLineNum = 1;
    Line currentLine{ currentLineNum, asmFile.GetFirstLine() };
    MatchInstructions(currentLine);
   
    while (!asmFile.Eof())
    {
        currentLineNum++;
        currentLine = Line{ currentLineNum, asmFile.GetNextLine() };
        MatchInstructions(currentLine);
    }

    UpdateInstructionListView();
}

void MainWindow::OnSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save Result ASM file"), "", "",
                                "ASM Files (*.s)|*.s", 
                                wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
 
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxTextFile resultsFile;
    resultsFile.Create(saveFileDialog.GetPath());

    for (auto& i : instructions)
    {
        for (auto& line : i.MatchingLines())
        {
            wxString lineToSave;
            lineToSave << line.Text();
            lineToSave << " # Line ";
            lineToSave << line.Number();
            lineToSave << ", ";
            lineToSave << i.Description();
            resultsFile.AddLine(lineToSave);
        }
    }

    if (!resultsFile.Write())
        wxMessageBox("Unable to write to disk", "AsmFinder", wxOK | wxICON_ERROR);
}

void MainWindow::OnImport(wxCommandEvent& event)
{
    wxFileDialog dialog(this);

    if(dialog.ShowModal() != wxID_OK) 
        return;

    wxString path = dialog.GetPath();
    wxTextFile instructionFile;
    instructionFile.Open(path);

    ParseInstructionDefinition(instructionFile.GetFirstLine());

    while (!instructionFile.Eof())
    {
        ParseInstructionDefinition(instructionFile.GetNextLine());
    }

    UpdateInstructionListView();
}

void MainWindow::OnExport(wxCommandEvent& event)
{
    wxMessageBox("Under Construction", "AsmFinder", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnAdd(wxCommandEvent& event)
{
    Instruction i{ nameTextCtrl->GetLineText(0), 
                   descriptionTextCtrl->GetLineText(0) };
    instructions.push_back(i);
    UpdateInstructionListView();
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxString aboutInfo;
    aboutInfo << PROGRAM_NAME << '\n';
    aboutInfo << version;
    aboutInfo << PROGRAM_COPYRIGHT;
    wxMessageBox(aboutInfo, PROGRAM_NAME, wxOK | wxICON_INFORMATION);
}

void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainWindow::UpdateInstructionListView()
{
    constexpr int descIndex{ 1 };
    constexpr int foundIndex{ 2 };

    int itemIndex{ 0 };

    instructionListView->DeleteAllItems();

    for (auto& i : instructions)
    {
        wxString name = i.Name();
        wxString desc = i.Description();
        wxString found;
        found << i.MatchingLines().size();
        instructionListView->InsertItem(itemIndex, i.Name());
        instructionListView->SetItem(itemIndex, descIndex, desc);
        instructionListView->SetItem(itemIndex, foundIndex, found);
        itemIndex++;
    }
}

void MainWindow::MatchInstructions(const Line& line)
{
    // This slows down exponentially based on the number of instructions to
    // process. TODO: rework Instruction::Match(Line) to speed this up.
    for (auto& instruction : instructions)
    {
        if (instruction.Match(line))
            break;
    }
}

void MainWindow::ParseInstructionDefinition(wxString line)
{
    int commaPosition = line.Find(',');

    if (commaPosition != wxNOT_FOUND)
    {
        size_t nameFrom{ 0 };
        size_t nameTo{ static_cast<size_t>(commaPosition) - 1 };
        size_t descFrom{ static_cast<size_t>(commaPosition) + 1 };
        size_t descTo{ line.Length() - 1 };
        wxString name = line.SubString(nameFrom, nameTo);
        wxString desc = line.SubString(descFrom, descTo);
        Instruction i{ name, desc };
        instructions.push_back(i);
    }
}