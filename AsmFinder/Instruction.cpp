// Instruction.cpp - Defines the Instruction class.
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

#include "Instruction.h"

bool Instruction::Match(const Line& line)
{
    constexpr bool trimFromRight{ true };
    constexpr bool trimFromLeft{ false };
    constexpr bool caseInsensitive{ false };

    // Convert both the line text and instruction name to lower case so
    // they can be more easily compared.
    wxString textLower = line.Text().Lower();
    wxString nameLower = name.Lower();

    // Obtain the position of the instruction name, if it exists, so we can
    // determine if the instruction is isolated from other text.
    int position = textLower.Find(nameLower);
    
    if (position != wxNOT_FOUND)
    {
        // Obtain all the text leading up to the instruction name so we can
        // see if it is isolated.
        size_t from = 0;
        size_t to = position + name.Length();
        wxString subString = textLower.SubString(from, to);

        // Remove the leading and trailing whitespace so we can look at the
        // instruction name and see if it is in isolation.
        wxString isolatedString = subString.Trim(trimFromRight);
        isolatedString = isolatedString.Trim(trimFromLeft);

        // If the instruction is indeed in isolation and not mistakenly part
        // of some other text, we consider it a match.
        if (isolatedString == nameLower)
        {
            matchingLines.push_back(line);
            return true;
        }
        else
        {
            return false;
        }
    }
    
    return false;
}