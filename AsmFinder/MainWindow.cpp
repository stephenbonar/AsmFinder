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
    panel = new wxPanel(this);

    InitVersion();
    InitMenuBar();
    InitStatusBar();
    InitControls();
    ConfigureLayout();
    Fit();
    InitEventBindings();
    UpdateControls();
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

void MainWindow::InitControls()
{
    nameLabel = new wxStaticText{ panel, wxID_ANY, "Instruction" };
    descriptionLabel = new wxStaticText{ panel, wxID_ANY, "Description" };
    fileLabel = new wxStaticText { panel, wxID_ANY, "Current File: <None>" };

    nameTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    descriptionTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    addButton = new wxButton(panel, ID::Add, "Add");
    searchButton = new wxButton(panel, ID::Search, "Search");

    instructionListView = new wxListView{ panel, wxID_ANY, wxDefaultPosition };
    instructionListView->AppendColumn("Instruction");
    instructionListView->AppendColumn("Description", wxLIST_FORMAT_LEFT, 300);
    instructionListView->AppendColumn("Found");

    resultListView = new wxListView{ panel, wxID_ANY };
    resultListView->AppendColumn("Line");
    resultListView->AppendColumn("Text", wxLIST_FORMAT_LEFT, 400);
}

void MainWindow::ConfigureLayout()
{
    wxSizerFlags addInstructionSizerFlags = wxSizerFlags{ 0 };
    addInstructionSizerFlags.Align(wxALIGN_CENTER_VERTICAL);
    addInstructionSizerFlags.Border(wxALL, 5);

    addInstructionSizer = new wxBoxSizer{ wxHORIZONTAL };
    addInstructionSizer->Add(nameLabel, addInstructionSizerFlags);
    addInstructionSizer->Add(nameTextCtrl, addInstructionSizerFlags);
    addInstructionSizer->Add(descriptionLabel, addInstructionSizerFlags);
    addInstructionSizer->Add(descriptionTextCtrl, 1, 
                             wxALIGN_CENTER_VERTICAL, 5);
    addInstructionSizer->Add(addButton, addInstructionSizerFlags);

    searchInstructionSizer = new wxBoxSizer{ wxHORIZONTAL };
    searchInstructionSizer->Add(searchButton, 0, 
                                wxALL | wxALIGN_CENTER_VERTICAL, 5);
    searchInstructionSizer->Add(fileLabel, 0,
                                wxALL | wxALIGN_CENTER_VERTICAL, 5);

    topSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Search" };
    topSizer->Add(addInstructionSizer, 0, wxEXPAND);
    topSizer->Add(instructionListView, 1, wxALL | wxEXPAND, 5);
    topSizer->Add(searchInstructionSizer);
    
    bottomSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Results" };
    bottomSizer->Add(resultListView, 1, wxALL | wxEXPAND, 5);

    panelSizer = new wxBoxSizer{ wxVERTICAL };
    panelSizer->Add(topSizer, 1, wxALL | wxEXPAND, 10);
    panelSizer->Add(bottomSizer, 1, wxALL | wxEXPAND, 10);

    panel->SetSizer(panelSizer);
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
    Bind(wxEVT_BUTTON, &MainWindow::OnSearch, this, ID::Search);
}

void MainWindow::UpdateControls()
{
    if (path == "")
    {
        EnableControls(false);
    }
    else
    {
        EnableControls();
    }

    UpdateInstructionListView();
    UpdateResultListView();
}

void MainWindow::EnableControls(bool enabled)
{
    nameTextCtrl->Enable(enabled);
    descriptionTextCtrl->Enable(enabled);
    addButton->Enable(enabled);
    searchButton->Enable(enabled);
    instructionListView->Enable(enabled);
    resultListView->Enable(enabled);
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

void MainWindow::UpdateResultListView()
{
    constexpr int textIndex{ 1 };
    int itemIndex{ 0 };

    resultListView->DeleteAllItems();

    for (auto& r : results)
    {
        wxString lineNumber;
        lineNumber << r.Number();
        resultListView->InsertItem(itemIndex, lineNumber);
        resultListView->SetItem(itemIndex, textIndex, r.Text());
        itemIndex++;
    }
}

void MainWindow::MatchInstructions(const Line& line)
{
    for (auto& instruction : instructions)
    {
        if (instruction.Match(line))
        {
            results.push_back(line);
            break;
        }
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

void MainWindow::ClearInstructionCounts()
{
    for (auto& instruction : instructions)
        instruction.ClearMatches();
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
    wxFileDialog dialog(this);

    if(dialog.ShowModal() != wxID_OK) 
        return;

    path = dialog.GetPath();
    fileLabel->SetLabelText("Current File: " + path);
    UpdateControls();  
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

    UpdateControls();
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
    UpdateControls();
}

void MainWindow::OnSearch(wxCommandEvent& event)
{
    if (instructions.size() == 0)
    {
        wxMessageBox("You must add at least one instruction to search for.",
                     "AsmFinder", wxOK | wxICON_INFORMATION);
        return;
    }
        
    EnableControls(false);
    ClearInstructionCounts();

    wxTextFile asmFile;
    asmFile.Open(path);

    std::vector<Line> lines;
    int currentLineNum{ 1 };
    Line currentLine{ currentLineNum, asmFile.GetFirstLine() };
    lines.push_back(currentLine);

    while (!asmFile.Eof())
    {
        currentLineNum++;
        currentLine = Line{ currentLineNum, asmFile.GetNextLine() };
        lines.push_back(currentLine);
    }

    asmFile.Close();

    for (auto& line : lines)
        MatchInstructions(line);

    UpdateControls();

    wxMessageBox("Complete", "AsmFinder", wxOK | wxICON_INFORMATION);
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