# CMakeLists.txt - CMakeLists for building the main program.
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

# Defines the locations of header files to include.
#set(INCLUDES ${PROJECT_SOURCE_DIR}/AsmFinder)

# Define the sources used to build the executable.
set(SOURCES AsmFinder.cpp MainWindow.cpp Instruction.cpp Line.cpp)

# Define the additional libraries the GUI needs to link with. 
set(LIBRARIES wx::net wx::core wx::base)

# Define the directories that contain the header files the programs include.
set(INCLUDES 
    ${PROJECT_BINARY_DIR}/AsmFinder)

# Configure the program version info from the main cmake project into the
# Version.h header, which is build into the program binary. This is done so
# we centrally update the program name, version, and copyright from cmake.
configure_file(Version.h.in Version.h)

# Define the executable target to build.
if(WIN32)
    add_executable(AsmFinder WIN32 ${SOURCES})
else()
    add_executable(AsmFinder ${SOURCES})
endif(WIN32)

# Statically link the MSVC runtime.
set_property(TARGET AsmFinder PROPERTY
             MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_sources(AsmFinder PRIVATE AsmFinder.rc)

# Include all the directories that contain headers that we need that are not
# in the current directory, otherwise the compiler won't find them.
target_include_directories(AsmFinder PUBLIC ${INCLUDES})

# Links the executable with the libraries. 
target_link_libraries(AsmFinder ${LIBRARIES})
