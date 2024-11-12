# CMakeLists.txt - CMakeLists for building AsmFinder.
#
# Copyright (C) 2024 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Set the minimum version of CMake needed to build the program.
cmake_minimum_required(VERSION 3.10.0)

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Defines the project metadata.
project(AsmFinder VERSION 0.75.0 LANGUAGES C CXX)
set(PROJECT_RELEASE "Alpha")
set(PROJECT_COPYRIGHT "Copyright (C) 2024 Stephen Bonar")

# Statically link wxWidgets.
set(wxBUILD_SHARED OFF)

# Include the main program in the project.
add_subdirectory(AsmFinder)

# Include wxWidgets in the project. 
add_subdirectory(wxWidgets)