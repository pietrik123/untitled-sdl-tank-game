# Contents
[Introduction](#introduction)

[Prerequisites](#prerequisites)

[Setup](#setup)

[Clone](#clone)

[Build](#build)

# Introduction
This is untitled tank 2D game project created in C++ with SDL 2.0 library.
# Prerequisites
Windows 7 SP1 - needed to install MS Visual Studio 17 Community Edition.
# Setup
Main development IDE is MS Visual Studio Community Edition. Please download it from here:

https://www.visualstudio.com/pl/thank-you-downloading-visual-studio/?sku=Community&rel=15

Download SDL2.0 SDK, prepared specially for this project:

https://www.dropbox.com/s/neda15344p7chgc/development.zip?dl=0

Extract <b>development.zip</b> to <b>C</b> drive .

After extraction directories should have following structure:
```sh
C\
|-development\
  |- sdl2_visual\
     |- include\
     |- lib\
     |  |- x86\
     |  |- x64\     
     |- sdl2_image\
     |  |-include\
     |  |-lib\
     |    |- x86\
     |    |- x64\  
     |- sdl2_mixer\
        |-include\
        |-lib\
          |-x86\
          |-x64\
```
Download and install GIT:
https://git-scm.com/download/win
# Clone
To clone repository, open Windows Command Line and navigate to directory, in which you would like to work:
```sh
$ git clone https://github.com/pietrik123/untitled-sdl-tank-game.git
```
# Build
Please run MS Visual Studio. 

File -> Open -> Project/Solution ...

Navigate to the directory, where project files are stored.

Select Solution Platform. It has to be: <b>x86</b>.

From the main upper menu please select:

Project -> Properties ...

In configuration (general) please expand: "Windows SDK" and select version of SDK, which is present on your system (for example 10.0.14393.0). Click "Apply" and "Ok".

From upper menu select:

Compilation -> Compile solution ...


