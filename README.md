# Graphics-Algorithms
Fundamental algorithms of Computer graphics written with GLUT


# GLUT SETUP (Windows)
You need to set up glut to run the codes

1. Setup [CodeBlocks 10.05](https://sourceforge.net/projects/codeblocks/files/Binaries/10.05/Windows/codeblocks-10.05mingw-setup.exe/download) with minGW 
2. Download the GLUT files from [here](https://github.com/faridulreza/Graphics-Algorithms/tree/main/glut-3.7.6)
   - This version of GLUT was tested with CodeBlocks 10.05 only. Other verions may not work properly
3. Copy glut32.dll to C:\windows\System32 (if 32-bit OS) or to C:\windows\SyWOW64 (if 64-bit OS)
4. Copy glut32.lib to C:\Program Files (x86)\CodeBlocks\MinGW\lib
5. Copy glut.h to C:\Program Files (x86)\CodeBlocks\MinGW\include\GL


# Running the sample project:
- Open Codeblocks -> New Project -> GLUT project
- Browse location to C:\Program Files(x86)\CodeBlocks\MinGW (if needed)
- Browse glut location to C:\Program Files (x86)\CodeBlocks\MinGW (if needed) 
- ##### include <windows.h> header file in the main.cpp (this should be included at the top of all the #include directives) 
- Build and Run

If you see a lot of cool rotating objects, you ready to go.

