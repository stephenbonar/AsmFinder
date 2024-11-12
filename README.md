# AsmFinder

AsmFinder is a cross-platform C++ application that searches for specific assembly language instructions in a source file. The instructions to search can either be added manually at runtime or imported from a file. The program will tell you how many times each defined instruction occured in a file, and you can save the results (including line numbers) in a separate source file.

# Pre-Release Warning

This program is currently available in an early alpha pre-release. The program has only been tested on Windows and has not yet been thoroughly tested for bugs. Use at your own risk.

# Basic Instructions

Enter each assembly language instruction you want to search for by typing it into the *Instruction* text field and clicking the *Add* button. Then, open the file you want to search by clicking File -> Open. The program will show you how many occurances of each instruction were found in the text file. If you want to see the lines it found containing those instructions, you can save the results in a separate assembly language file by clicking File -> Save. 

As an alternative to manually entering each instruction you want to find, you can create a text file with each instruction on its own line and click File -> Import to import the instruction definitions from the file. Each line in the text file must be in the following format:

instruction,description

# Compiling

Use CMake to build the source code for your current platform. Only Windows has been tested so far.