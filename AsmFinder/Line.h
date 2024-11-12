// Line.h - Declares the Line class.
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

#ifndef LINE_H
#define LINE_H

#include <wx/wx.h>

/// @brief Represents a line from an assembly language source file.
class Line
{
public:
    /// @brief Constructor; creates a new instance of Line.
    /// @param number The line number in the file.
    /// @param text The text of the line.
    Line(int number, wxString text) : number{ number }, text{ text}
    { }
    
    /// @brief Gets the line number in the file.
    /// @return An integer representing the line number in the file.
    int Number() const { return number; }

    /// @brief Gets the text of the line.
    /// @return A wxString containing the text of the line.
    wxString Text() const { return text; }
private:
    int number;
    wxString text;
};

#endif