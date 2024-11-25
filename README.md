# AsmFinder

AsmFinder is a cross-platform C++ application that searches for specific assembly language instructions in a source file, telling you how many times they occur and on what lines.

# Pre-Release Warning

This program is currently available in an early alpha pre-release. While the program has been tested on Windows, macOS, and Linux, it has not yet been thoroughly tested for bugs. Use at your own risk.

# Features

AsmFinder supports the following features as of the latest alpha release:

-Adding individual instructions to search for via the UI
-Importing a list of instructions to search for in bulk
-Opening a source file but not searching it until you press the Search button
-Counts of how many times an instruction is found
-A result list showing the line numbers in the file that contain that instruction
-Saving the matching lines in a separate source file for analysis, including line numbers as comments
-Support for Windows, macOS, and Linux

Planned features for the final v1.0 release include:

-Showing the search results in context of the original file
-The ability to jump to a specific line in the file based on the search results

# How to Use

Enter each assembly language instruction you want to search for by typing it into the *Instruction* text field and clicking the *Add* button. Then, open the file you want to search by clicking File -> Open. Finally, press the *Search* button to see the results. The program will show you how many occurances of each instruction were found in the text file, as well as the lines in the file that contain the instructions you are searching for. You can also export the matching lines to a separate file with the original line numbers as comments by clicking File -> Save. 

As an alternative to manually entering each instruction you want to find, you can create a text file with each instruction on its own line and click File -> Import to import the instruction definitions from the file. Each line in the text file must be in the following format:

instruction,description

# Compiling

Use CMake to build the source code for your current platform. More detailed instructions to come soon.