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
    // Basically all we're doing here now is a compare. Initially, we tried to
    // tokenize each line and instruction name in this method, but that
    // resulted in horrendous times (3:11:83 for 321,379 lines). However, by
    // pre-tokenzing each line as its read in from the file and pre-tokenizing
    // the instruction name, the same number of lines takes 0:09:03.
    if (token == line.FirstToken())
    {
        matchingLines.push_back(line);
        return true;
    }
    
    return false;
}