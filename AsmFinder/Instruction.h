// Instruction.h - Declares the Instruction class.
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

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <wx/wx.h>
#include "Line.h"

/// @brief Represents an assembly language instruction.
class Instruction
{
public:
    /// @brief Constructor; creates a new instance of Instruction.
    /// @param name The name of the instruction.
    /// @param description The instruction's description.
    Instruction(wxString name, wxString description) 
        : name{ name }, description{ description }
    {}

    /// @brief Gets the name of the instruction. 
    /// @return A wxString representing the name of the instruction.
    wxString Name() const { return name; }

    /// @brief Gets the instruction's description.
    /// @return A wxString containing the instruction's description.
    wxString Description() const { return description; }

    /// @brief Obtains the lines that have the instruction in them.
    /// @return A vector of lines from the assembly language source file.
    std::vector<Line> MatchingLines() const { return matchingLines; }

    /// @brief Determines if the specified line has this instruction.
    /// @param line The line to check.
    /// @return True if the line contains the instruction, otherwise false.
    /// @post MatchingLines() will contain line if it matches.
    bool Match(const Line& line);
private:
    wxString name;
    wxString description;
    std::vector<Line> matchingLines;
};

#endif